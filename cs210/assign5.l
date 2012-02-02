(defun the-family () 
	(sort (remove () (mapcar 'first family))#'string-lessp))
(defun father (x)
        (apply 'append (last (assoc x family))))
(defun mother (x) 
	(append (second (assoc x family))))
(defun parents (x)
        (append (remove () (rest (assoc x family)))))
(defun grandparents (x)
        (remove () (apply 'union (mapcar #'parents
                                (parents x)))))

(defun children (x)
  (mapcan #'(lambda (z) (if (member x (cdr z)) (list (car z)))) family))

(defun siblings (x)
  (if (assoc x family) (remove x (union (children (first (parents x))) (children (second (parents x)))))))

(defun full-siblings (x)
  (remove x (mapcan #'(lambda (z) 
        (if (equal (parents x) (cdr z)) 
	     (list (car z)))) family)))

(defun ancestors (x)
 (if (not(eq x ())) (remove () (union (cons (first (parents x)) (ancestors (first (parents x)))) (cons (second (parents x)) (ancestors (second (parents x))))))))

(defun descendants (x)
(if (not(eq x ()))  (nconc (children x)(mapcan 'descendants (children x)))))

(defun half-siblings (x)
        (remove x (set-difference 
		(siblings x) (full-siblings x))))

(defun aunts-uncles (x)
       (remove (second (parents x))(remove (first (parents x)) (union (full-siblings (first (parents x))) (full-siblings (second (parents x)))))))

(defun first-cousins (x)
(remove x (apply #'append (mapcar #'children (aunts-uncles x)))))

(defun matep (x y)
(if (if (intersection (children x) (children y)) T) (not(eq x y))))

(defun siblingp (x y)
 (if (if (intersection (parents x) (parents y))(not(eq x y))) (intersection (parents x) (parents y))))

