(defun the-family 
	(remove nil (remove-duplicates (apply #'append family))))
(defun father (x) 
	(last (assoc x family)))
(defun mother (x) 
	(second (assoc x family)))
(defun parents (x) 
	(rest (assoc x family)))
(defun grandparents (x) 
	(apply 'append (mapcar #'parents 
				(parents x))))
(defun children (x)
  (mapcan #'(lambda (z) (if (member x (cdr z)) (list (car z)))) family)
)

(defun siblings (x)
  (remove x (children (first (parents x)))))

(defun full-siblings (x)
  (remove x (mapcan #'(lambda (z) 
        (if (equal (parents x) (cdr z)) 
	     (list (car z)))) family)))

 (defun half-siblings (x)
        (remove x (set-difference 
		(siblings x) (full-siblings x))))
(defun aunts-uncles (x)
        (union (full-siblings (first (parents x))) (full-siblings (second (parents x)))))

(defun first-cousins (x)
(remove x (apply #'append (mapcar #'children (aunts-uncles x)))))

(defun matep (x y)
 (if (member y (apply #'append (mapcan #'(lambda (z) (if (member x (cdr z)) (list (last z)))) family))) T))

(defun siblingp (x y)
 (if (eq (first (parents x)) (first (parents y))) T) (if (eq (second (parents x)) (second (parents y)))T) (if (eq x y))

