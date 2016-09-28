;;;Dean Landes and Steven Rosendahl

;;-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
;;POSITIVE
;;-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
(defun positive(n)
    (cond
        ((null n)        0)
        ((and (null(cdr n)) (< (car n) 0))    0)
        ((null(cdr n))    n)
        (T
            (cond
                ((and (or (> (car n) 0) (= (car n) 0)) (or (> (car(cdr n)) 0) (= (car(cdr n)) 0)))
                (positive(cons (+ (car n) (car(cdr n))) (cdr(cdr n)))))

                ((< (car(cdr n)) 0)
                (positive(cons (car n) (cdr(cdr n)))))

                (T
                (positive(cdr n)))
            )
        )
    )
)

;;-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
;;SORTED
;;-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
(defun sorted(n)
    (cond
        ((null n )        T)
        ((null(cdr n))    T)
        (T
            (if (> (car n) (car(cdr n)))
                NIL
            )
            (if (or (< (car n) (car(cdr n))) (= (car n) (car(cdr n))))
                (sorted(cdr n))
            )
        )
    )
)

;;-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
;;BUBBLE
;;-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
(defun bubble(n)
    (cond
        ((null n) NIL)
        ((null (cdr n)) n)
        (T
            (if (< (car n)(car(cdr n)))
                (cons (car n)(bubble(cdr n)))
                (cons (car(cdr n))(bubble(cons (car n) (cdr (cdr n)))))
            )
        )
    )
)

;;-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
;;BUBBLESORT
;;-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
(defun bubblesort(n)
    (cond
        ((null n)    NIL)
        ((sorted n)    n)
        (T
            (bubblesort(bubble n))
        )
    )
)
