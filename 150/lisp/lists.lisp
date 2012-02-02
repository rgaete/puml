(defun splice (L1 L2) listp '((CAR L1) (CAR L2)))
(if (eql (cdr L2) nil)
(splice (cdr L1) (cdr L2))))

