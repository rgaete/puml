(setq *echo* NIL)      ;; echo the SEND messages
(setq *echoall* NIL)   ;; echo all of the message passing including internals
;; add the classic putprop function using setf
;; putprop is the old name used by many lisps but
;; no longer available in common lisp.
(defun putprop (sym value name) (setf (get sym name) value))

;; add addprops which allows a property list to be added to
;; the property list of a symbol
(defun addprops (sym list)
       (when list
             (putprop sym (second list) (first list))
             (addprops sym (rest (rest list)))
             )
)

;; increment a number associated with a property by delta
;; can be used to increase or decrease a property value by delta
(defun incprop (sym delta name) (if (numberp (get sym name))
                                    (putprop sym (+ (get sym name) delta) name)
                                    (putprop sym delta name)))


(defun nl () (princ "
") T)


;;;; ;;;;  ;;;;  ;;;;  ;;;;  ;;;;  ;;;;  ;;;;  ;;;;  ;;;;  ;;;;
;;;;
;;;;  This file implements a subset of MMOO (The Moscow MOO)
;;;;
;;;;
;;;;
;;;;
;;;; ;;;;  ;;;;  ;;;;  ;;;;  ;;;;  ;;;;  ;;;;  ;;;;  ;;;;  ;;;;

;;; Each object is a symbol at the global level.  Properties for the
;;; symbol store both data and methods.  Messaging is done with a
;;; collection of send functions.  This will provide us with powerful
;;; data abstraction, but we don't get to control the access to the
;;; data this implementation.
;;;
;;; There is no distinction between class and instance in this
;;; implementation.  Any object can be subclassed (specialized).
;;; "Class objects" can be invoked as objects because they are
;;; objects.  This is kind of an unusual approach but it simplifies
;;; our life.
;;;
;;; Ultimately we will have these relations: isa, containment, and
;;; direction are implemented and every object has a set of methods
;;; stored in the the property verbs
;;;
;;; We test if a symbol is an object by testing if it has a non-nil
;;;   object property.
;;;
;;; THE PROPERTIES ;;; ;;; ;;; ;;; ;;; ;;; ;;; ;;; ;;; ;;; ;;; ;;; ;;;
;;;
;;; NAME a printable name for the object
;;;     name - a STRING that is a few word description of the object
;;;
;;; ISA properties with EVERY OBJECT
;;;     children - a LIST of direct decendants to an object
;;;     parent - a SYMBOL that is the parent (NIL if the primordial object)
;;;
;;; METHODS on EVERY OBJECT are stored in the property:
;;;     verbs - an ALIST of verb name as a symbol and the code that implements
;;;              the action
;;;
;;; CONTAINMENT (ownership) properties with EVERY OBJECT
;;;    contains - a LIST of all of the things contained in this object
;;;    location - a SYMBOL of the object that contains this object (NIL
;;;                 if not contained)
;;;
;;; DIRECTION (links between objects and property of PLACE but not THING)
;;;    direction - an ALIST whose key is the direction to go and whose
;;;                  data portion (second) is a list of description
;;;                  of what is in that direction and the object that
;;;                  is linked to in that direction.  For example:
;;;
;;;                     ((N (" on a path north" NPATH))
;;;                      (E (" to a fountain" SPATH))
;;;                      (S (" on a path south" SPATH))
;;;                      (W (" into a cabin" CABIN))
;;;                      (IN ("in the door of a rustic cabin" CABIN))
;;;                     )
;;;
;;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;;

;; property accessors
(defun objectp (sym) (get sym 'object))
(defun myname (sym) (get sym 'name))
(defun myparent (sym) (get sym 'parent))
(defun mychildren (sym) (get sym 'children))
(defun myverbs (sym) (mapcar 'first (get sym 'verbs)))
(defun mydirs (sym) (get sym 'dirs))
(defun mylocation (sym) (get sym 'location))
(defun mycontains (sym) (get sym 'contains))


;;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;;
;;;
;;; list utilities
;;;

;; print out a comma separate version of the list
(defun princ-list (list)
  (cond ((atom list) (princ list))
        ((= 2 (length list)) (princ (car list))
         (princ " and ")
         (princ (car (cdr list)))
         )
        ((= 1 (length list)) (princ (car list)))
        (T (princ (car list)) (princ ", ") (princ-list (cdr list)))
        )
  T
  )


;;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;;
;;;
;;; lisp expression utilities
;;;

;; this will create a copy of a structure
(defun copy (l)
  (cond ((atom l) l)
        (T (mapcar 'copy l))
        )
  )


;;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;;
;;;
;;; alist utilities
;;;
(princ "Alists tools")(nl)

;; replace the value of sym in the alist with value.  If sym not there then
;; add it.
(defun subst-alist (sym value alist)
  (cond ((null alist) (list (list sym value)))
        ((eq (car (car alist)) sym) (cons (list sym value) (cdr alist)))
        (T (cons (car alist) (subst-alist sym value (cdr alist))))
        )
  )

;; remove the sym from the alist
(defun rem-alist (sym alist)
  (mapcan #'(lambda (x) (if (eq sym (car x)) NIL (list x))) alist)
  )

;; get keys from an alist (a trivial function)
(defun get-keys-alist (alist)
  (mapcar 'car alist)
  )


;; merge two alists so the primary alist is augmented by any elements of secondary
;; which have keys not found in the primary
(defun merge-alists (primary secondary)
    (cond ((null secondary) primary)
          ((assoc (first (first secondary)) primary) (merge-alists primary (rest secondary)))
          (T (cons (first secondary) (merge-alists primary (rest secondary))))
    ))


;;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;;
;;;
;;; property list tools
;;;
;;; directly manipulate lists that are associated with a property
;;;
(princ "Property list tools")(nl)


;; put the value onto the list associated with the symbol's property prop
(defun push-onto-prop (sym value prop)
  (putprop sym (cons value (get sym prop)) prop)
  )

;; remove the value from the list associated with the symbol's property prop
(defun rem-from-prop (sym value prop)
  (putprop sym
           (mapcan #'(lambda (x) (if (eq x value) NIL (list x)))
                   (get sym prop)
                   )
           prop
           )
  )

;; get the list of properties of a symbol
(defun get-prop-syms-aux (proplist)
  (cond ((null proplist) NIL)
        (T (cons (car proplist) (get-prop-syms-aux (cdr (cdr proplist)))))
        )
  )
(defun get-prop-syms (sym) (get-prop-syms-aux (symbol-plist sym)))


;;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;;
;;;
;;; parenting (inheritance)
;;;
;;; atomic parenting ops
;;;
(princ "Parenting (inheritance)")(nl)


;; make parent-sym the parent of sym
(defun parent (sym parent-sym)
  (push-onto-prop parent-sym sym 'children)
  (putprop sym parent-sym 'parent)
  )

;; undo the parent sym relationship
(defun unparent (sym)
  (cond ((myparent sym)
         (rem-from-prop (myparent sym) sym 'children)
         (putprop sym NIL 'parent)
         )
        )
  )

;; reparent an object
(defun reparent (sym newparent)
  (unparent sym)
  (parent sym newparent)
  )


;; ask if an object is of a given type
(defun isap (sym type)
  (cond ((eq sym type))
        ((myparent sym) (isap (myparent sym) type))
        )
  )


;;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;;
;;;
;;; send (message passing)
;;;
;;; If the method doesn't exist the send returns NIL but is otherwise
;;;  quiet about it since this may be a ligit desire.
;;;
;;; Sending a message to a symbol that is not an object will report
;;; an error and return NIL.
;;;
;;; Send-to is the workhorse of send.  It needs to keep track of not
;;;  only the object to which the message is being sent but also the
;;;  original object to which the message was sent called the
;;;  truetype.  This is because a superclass of the truetype may
;;;  implement the called method and that may, in turn, invoke another
;;;  method that is actually supported in the truetype.
;;;
;;; Send-super is like send-to in that it takes a truetype as well
;;;  as the called type
;;;
(princ "The send utilities")(nl)

;; SYM <- VERB,TYPE
(defun send-to (sym truetype verb &optional args)
  (if *echoall* (print (list "SEND-TO:" sym truetype verb args)))
  (cond ((not (objectp sym))
         (princ "attempt to send ")
         (princ verb)
         (princ " to ")
         (princ sym)
         (princ " which is not an object.")(nl)
         NIL
         )
        ((get-verb-func sym verb)
         (cond (args (funcall (get-verb-func sym verb) truetype args))
               (T           (funcall (get-verb-func sym verb) truetype))
         ))
        ((myparent sym)
         (send-to (myparent sym) truetype verb args) ;; same as send-super
         )
        )
  )


;; SYM <- VERB
;; note that both the object that receives the message and the
;; truetype START OUT the same in the send-to call.
(defun send  (sym verb &optional args)
  (if (or *echo* *echoall*) (print (list 'SEND sym verb args)))
  (send-to sym sym verb args)
  )


;; PARENT(SYM) <- VERB
(defun send-super (sym truetype verb &optional args)
  (if *echoall* (print (list 'SEND-SUPER sym truetype verb args)))
  (cond ((myparent sym) (send-to (myparent sym) truetype verb args)))
  )


;; (LIST) <- VERB
;; sends the same message and arg to each object in list
;; Note that the return value is the value of list.
(defun send-list (list verb &optional args)
  (mapc #'(lambda (x) (send x verb args)) list)
  )

;; SYM <- VERB num times
(defun send-times (sym num verb &optional args)
  (dotimes (x num) (send sym verb args))
)


;; returns the object that will support the given verb for
;; the truetype object sym
(defun who-supports-verb (sym verb)
  (cond ((get-verb-func sym verb) sym)
        ((myparent sym)
         (who-supports-verb (myparent sym) verb)
         )
        )
)

;; create an alist of all verbs supported and by the object
(defun allverbs (sym) (if sym (cons (list sym (myverbs sym)) (allverbs (myparent sym))) NIL))

;;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;;
;;;
;;; MOO object creation and destruction
;;;
;;; objects have an isa hierarchy.
;;;
;;;  NOTE: and object named sym is created a (setq sym sym) is done
;;;  which means that all future references to sym can be done unquoted.
;;;  This means the first time you mention an object it must be quoted
;;;  but need not be thereafter.
;;;
;;;  Also note that the function value of the symbol for the object
;;;  is assigned a function that sends a message to the object.  This
;;;  means that (send obj verb) can be done by saying (obj verb)
;;;
(princ "MOO object creation and destruction")(nl)


;; add an object to the world
(defun addo (sym name parent &rest properties)
  (mapc #'(lambda (x) (putprop sym NIL x)) ;; clone all the data names
        (get-prop-syms parent)
        )
  (putprop sym T 'object)  ;; mark as an object
  (putprop sym name 'name) ;; overwrite printable name
  (parent sym parent)      ;; parent the object
  (set sym sym)            ;; for convenience sym <- sym
  (setf (symbol-function sym) #'(lambda (verb  &optional args)
                                  (send sym verb args)))
  (addprops sym properties)
  (send sym 'init)         ;; init the new object which will default to parent
  sym                      ;; return the symbol
  )


;; remove the object from the hierarchy
;; NOTE: we remove all properties to reset the symbol destroying the object
(defun remo (sym)
  (mapc #'(lambda (x) (reparent x (myparent sym)) x)
        (mychildren sym)
        )
  (unparent sym)
  (mapc #'(lambda (x) (remprop sym x)) (get-prop-syms sym))
  (remprop sym 'object)   ;; remove the object marker
  )


;; insert the object into the hierarchy by placing the new object
;; between the parentsym and its children
(defun inserto (parentsym new-object name)
  (mapc #'(lambda (x) (if (not (eq x new-object)) (reparent x new-object)))
        (mychildren parentsym)
        )
  (reparent new-object parentsym)
  )


;; report the entire hierarchy below obj
(defun descendants (obj)
   (if (mychildren obj)
       (cons obj (mapcar 'descendants (mychildren obj)))
        obj
   )
)


;; report where the object is in the hierarcy
(defun ancestors (obj)
   (if (myparent obj)
       (cons obj (ancestors (myparent obj)))
       (list obj)
   )
)


;;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;;
;;;
;;; MOO verbs (methods)
;;;
;;;  The first time you mention a method name it must be quoted
;;;  but you need not be thereafter.
;;;
(princ "MOO verbs")(nl)


;; utility get the code for method verb-name on a given function
;; does not do inheritance (that is handled by the send commands).
;; This can be used to see if a method is defined.
(defun get-verb-func (sym verb-name)
  (second (assoc verb-name (get sym 'verbs)))
  )


;; add a method onto object sym
(defun addv (sym verb-name code)
  (putprop sym
           (subst-alist verb-name code (get sym 'verbs))
           'verbs
           )
  (set verb-name verb-name)
  )


;; remove a verb
(defun remv (sym verb-name)
  (putprop sym
           (rem-alist verb-name (get sym 'verbs))
           'verbs
           )
  verb-name
  )


;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;;
;;
;; directions
;;
;; how this is stored on the dir property:
;; ((N (" on a path north" NPATH))
;;  (E (" to a fountain" SPATH))
;;  (S (" on a path south" SPATH))
;;  (W (" into a cabin" CABIN))
;;  (IN ("in the door of a rustic cabin" CABIN))
;; )
;;
(princ "Directions")(nl)

;; maintain a list of opposite directions for double linking space
(defun opposite-dir (dir)
  (or (second (assoc dir '((n s)
                           (s n)
                           (e w)
                           (w e)
                           (up down)
                           (down up)
                           (in out)
                           (out in)
                           (under over)
                           (over under)
                           )
                     ))
      dir
      )
  )


;; add a direction to an object sym.  The name of the direction is dirname
;; the description of that direction is detail and going in that direction
;; takes you to nextsym
(defun adddir (sym dirname detail nextsym)
  (putprop sym
           (subst-alist dirname (list detail nextsym) (get sym 'dirs))
           'dirs
           )
  (set dirname dirname)
  )


;; get the directions available from an object sym
(defun getdirsym (sym dirname)
  (if (assoc dirname (get sym 'dirs))
      (second (second (assoc dirname (get sym 'dirs))))
    )
  )


;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;;
;;
;; containment
;;
;; In this world location is maintained by containment
;;
(princ "Containment")(nl)


;; quietly ask if sym is at contained by loc
(defun isinp (sym loc)
  (and (objectp sym)
       (member sym (mycontains loc))
       )
  )


;; is an object of type (is or has parent type) contained in self?
(defun contains-typep (self type)
  (some #'(lambda (x) (isap x type)) (mycontains self))
)


;; place object sym in location newloc
(defun place-in (newloc sym)
  (cond ((isinp sym newloc)
         (princ (myname sym))
         (princ " is already in ")
         (princ (myname newloc))
         (princ ".")(nl)
         NIL
         )
        (T
         (push-onto-prop newloc sym 'contains)
         (putprop sym newloc 'location)
         )
        )
  )

;; drop an object
(defun unplace (sym)
  (cond ((mylocation sym)
         (rem-from-prop (mylocation sym) sym 'contains)
         (putprop sym NIL 'location)
         T
         )
        (T  (princ (myname sym))
            (princ " has no location and so can't be moved.")(nl)
            NIL
            )
        )
  )

;; move object sym to a new location
(defun move (sym newloc)
  (and (objectp sym)
       (objectp newloc)
       (unplace sym)
       (place-in newloc sym)
       )
  )


;;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;;
;;;
;;; object tree utilities
;;;

;; list all the objects starting at obj and going down the tree
(defun listobj (obj) (cond ((mychildren obj)
                            (append (list obj)
                                    (mapcan 'listobj (mychildren obj))))
                           (T (list obj))))

;; list class hierarchy in nested format
(defun treeobj (obj) (cond ((mychildren obj)
                            (cons obj
                                  (mapcar 'treeobj (mychildren obj))))
                           (T obj)
))

;; this is like mapc for the object hierarchy
;; this also demonstrates the creation of a closure which defines one
;; of two arguments to mapobj so it can be called with mapc
(defun mapobj (f obj) (cond ((mychildren obj)
                            (append (list (funcall f obj))
                                    (mapcan #'(lambda (z) (mapobj f z))
                                            (mychildren obj))
                                    ))
                           (T (list (funcall f obj)))
))

;;  these examples print the list of objects and their parents
;;  and the objects and their verbs
;; (mapobj #'(lambda (x) (print (list x (myparent x)))) thing)
;; (mapobj #'(lambda (x) (print (if (myverbs x)
;;                                 (list x (myverbs x))
;;                               (list x))))
;;        thing)


;;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;;
;;;
;;; Define world
;;;
(princ "Define world: the objects")(nl)


;; THING  ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;;
(princ "THING")(nl)
;; data
(putprop 'thing T 'object)       ;; mark as object
(putprop 'thing "a thing" 'name) ;; my printable name
(putprop 'thing NIL 'parent)     ;; my parent
(putprop 'thing NIL 'children)   ;; my children
(putprop 'thing NIL 'contains)   ;; who I contain
(putprop 'thing NIL 'location)   ;; who contains me
(putprop 'thing NIL 'verbs)      ;; actions on me
(setq thing 'thing)              ;; all objects point to themselves
;;  NOTE: dirs is a property of PLACE and not THING (see below)

;; utilities
(defun listout (l)
  (mapc #'(lambda (x)
            (princ "There is ")
            (princ (myname x))
            (princ " (")
            (princ x)
            (princ ") ")
            (princ " here.")(nl)
            )
        l
        )
  T
  )

(defun listdir (l)
  (if l (princ "From here you can: ")(nl))
  (mapc #'(lambda (x)
            (princ "go ")
            (princ (first x))
            (princ " ")
            (princ (first (second x)))
            (princ ".")(nl)
            )
        l
        )
  T
  )

;; methods
(addv thing 'hi
      #'(lambda (self) (princ (myname self)) (princ " says hi")(nl) T)
      )


(addv thing 'look
      #'(lambda (self) (nl)(princ "You see ")
          (princ (myname self))
          (princ ".")(nl)
          (listout (mycontains self))
          T
          )
      )


;; ANIMAT ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;;
(princ "ANIMAT")(nl)
(addo 'animat "animated thing" thing)

;; methods
(addv animat 'go
      #'(lambda (self arg)
          (cond ((getdirsym (mylocation self) arg)
                 (move self (getdirsym (mylocation self) arg))
                 (send self look)
                 )
                (T (princ "You can't go that way.")(nl)
                   (listdir (mydirs (mylocation self)))
                   )
                )

          )
      )


(addv animat 'where
    #'(lambda (self) (princ (myname self))
        (princ " is in ")
        (princ (myname (mylocation self)))
        (nl) t)
)


(addv animat 'take
      #'(lambda (self arg)
          (cond ((isinp arg (mylocation self))
                 (send arg 'taken)
                 (move arg self)
                 T
                 )
                ( T (princ "I do not see ")
                    (princ (myname arg))
                    (princ " here.")(nl)
                    NIL
                    )
                )
          )
      )


(addv animat 'drop
      #'(lambda (self arg)
          (cond ((isinp arg self) (move arg (mylocation self))
                 (send arg 'dropped self)
                 T
                 )
                ( T (princ "I see no ")
                    (princ (myname arg))
                    (princ " here.")(nl)
                    NIL)
                )
          )
      )


(addv animat 'dropin
      #'(lambda (self item place)
          (print (list self item place))
          (cond ((isinp item self) (move item (mylocation self))
                 (send item 'dropped self)
                 T
                 )
                ( T (princ "I see no ")
                    (princ (myname item))
                    (princ " here.")(nl)
                    NIL)
                )
          )
      )


(addv animat 'list-have
      #'(lambda (self)
          (cond ((mycontains self)
                 (mapc #'(lambda (x)
                           (princ "You have ")
                           (princ (myname x))
                           (princ " (")
                           (princ x)
                           (princ ") ")(nl)
                           )
                       (mycontains self)
                       )
                 T
                 )
                )
          )
      )


(addv animat look
      #'(lambda (self) (send (mylocation self) 'look)
          (send self list-have)
          )
      )


;; PLACE ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;;
(princ "PLACE")(nl)
(addo 'place "place" thing 'dirs NIL)   ;; add the dirs data
;; methods
(addv place look
      #'(lambda (self) (send-super 'place self 'look) (listdir (mydirs self)))
      )


;; CABIN ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;;
(princ "CABIN")(nl)
(addo 'cabin "the inside of a rustic cabin" place)

(adddir cabin 'out "out the door" 'cabinext)


;; CABINEXT  ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;;
(princ "CABINEXT")(nl)
(addo 'cabinext "the outside of a rustic cabin in the woods" place)

(adddir cabinext 'in "into the cabin" 'cabin)
(adddir cabinext 'n " on a path north" 'npath)
(adddir cabinext 'e " to a fountain" 'fountain)
(adddir cabinext 's " on a path south" 'spath)
(adddir cabinext 'w " to a twisty path" 'twisty)

;; NPATH  ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;;
(princ "NPATH")(nl)
(addo 'npath "the frozen north" place)
(adddir npath 's " to a rustic cabin" cabinext)


;; SPATH  ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;;
(princ "SPATH")(nl)
(addo 'spath "the watery desert" place)
(adddir spath 'n " to a rustic cabin" cabinext)


;; FOUNTAIN  ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;;
(princ "EPATH")(nl)
(addo 'fountain "an ornate stone fountain" place)
(adddir fountain 'w " to a rustic cabin" 'cabinext)


;; TWISTY  ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;;
(princ "WPATH")(nl)
(addo 'twisty "a twisty path" place)
(adddir twisty 's " to a rustic cabin" 'cabinext) ;; not opposite dir
(adddir twisty 'n "a twisty path" twisty)
(adddir twisty 'e "a twisty path" twisty)
(adddir twisty 'w "a twisty path" twisty)


;; MARBLE  ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;;
(princ "MARBLE")(nl)
(addo 'marble "a shiny marble"  thing)

(place-in cabin marble)


;; BALL  ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;;
(princ "BALL")(nl)
(addo 'ball "a ball"  thing 'color "rubber")
(defun mycolor (sym) (get sym 'color))

(addv ball 'init #'(lambda (self) (print (list 'self self)) (send self setcolor (mycolor self))))
(addv ball 'setcolor #'(lambda (self arg) (putprop self arg 'color)
  (putprop self (concatenate 'string "a " arg " ball") 'name)))
(addv ball 'bounce  #'(lambda (self) (princ "BOING Boing boing")(nl) T))
(addv ball 'dropped  #'(lambda (self arg) (send self bounce)))


;; RBALL  ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;;
(princ "RBALL")(nl)
(addo 'rball "xxx" ball 'color "red")

(place-in cabinext rball)

;; YBALL  ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;;
(princ "YBALL")(nl)
(addo 'yball "xxx" ball 'color "yellow")

(place-in cabin yball)


;; I  ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;; ;;
(princ "I")(nl)
(addo 'I "me" animat)
(place-in cabin I)

;; methods
(addv I 'is-here-cond-check 
      #'(lambda (self arg)
          (cond ((or (isinp arg self) (isinp arg (mylocation self))) NIL)
                ( T (princ "I see no ")
                    (princ (myname arg))
                    (princ " here.")(nl)
                    T
                    ))))

(addv I 'take
      #'(lambda (self arg)
          (cond ((send-super I self take arg)
                 (princ "You take ")
                 (princ (myname arg))
                 (princ ".")(nl)
                 T     ;; after method would go here
                 )
                )
          )
      )

;; methods
(addv I 'drop
      #'(lambda (self arg)
          (cond ( T   ;; before method would go here
                 (princ "You drop ")
                 (princ (myname arg))
                 (princ ".")(nl)
                 (send-super I self drop arg)
                 T
                 )
                )
          )
      )

(treeobj thing)
