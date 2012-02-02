(defun contains-exactly-typep (self type)
(if (member type (mycontains self)) T))

(addo 'key "a key" thing)			      ;ADD KEY (THING)

(addo 'wu-key "a key for a windup toy" key)		      ;ADD WINDUP KEY (KEY)

(addo 'windup-toy "a windup-toy" animat (setq windnum 0))        ;ADD WINDUP TOY (THING)

(addo 'dog-key "a key for a windup dog" wu-key)			;DOG WINDUP KEY

;;;;;;;;;;;;;;;;;;;;;DUCK;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(addo 'duck "a windup duck" windup-toy )              ;ADD DUCK	(WINDUP TOY)

(addv duck 'sound #'(lambda (self) (princ "quack ")T))  ;DUCK's SOUND (QUACK)

;;;;;;;;;;;;;;;;;;;;;PIG;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(addo 'pig "a windup pig" windup-toy )              ;ADD PIG (WINDUP TOY)

(addv pig 'sound #'(lambda (self) (princ "oink ")T))  ;DUCK's SOUND (QUACK)

(addv pig 'windup-sound #'(lambda (self) (princ "squeal ")T))  ;DUCK's SOUND (QUACK)

;;;;;;;;;;;;;;;;;;;;;;DOG;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(addo 'dog "a windup dog" windup-toy)		       ;ADD DOG (WINDUP TOY)

(addv dog 'right-keyp #'(lambda (self) (contains-exactly-typep I dog-key)))

(addv dog 'sound #'(lambda (self) (princ "bark ")T))  ;DOG's SOUND (BARK)

;;;;;;;;;;;;;;;;;;;;;BABE;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(addo 'babe "babe the gallant pig" pig)              ;ADD BABE (PIG)


;;;;;;;;;;;;;;;;;;;;;;WINDUP-TOY;;;;;;;;;;;;;;;;;;;;;;;;;

(addv windup-toy 'sound #'(lambda (self) (princ "tick ") T))

(addv windup-toy 'dropped #'(lambda (self arg) (if (if (if (> windnum 0) (princ (myname self))) (princ " says: ")) (send-times self windnum sound))  (if (= windnum 0) (princ (myname self))) (if (= windnum 0) (princ " sits there.")) (setq windnum 0)T))

(addv windup-toy 'windup-sound #'(lambda (self) (princ "click ") T))

(addv windup-toy 'right-keyp #'(lambda (self) (contains-exactly-typep I wu-key)))

(defun windup-error (self) 
(princ "you can't windup ") (princ (myname self)) (princ " unless you have the right key.")())

(addv windup-toy 'windup #'(lambda (self arg)(if (if (if (if (if (if (send self right-keyp) (princ "You place the key in the ")) (princ (myname self))) (princ " and turn it:"))  (nl)) (setq windnum (+ windnum arg)))(send-times self arg windup-sound)) (if (not (send self right-keyp))(windup-error self)T)))
