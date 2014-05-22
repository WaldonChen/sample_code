;;;; recursive.lisp
;;;;    Implement anonymous recursive function
;;;;
;;;; FIX(F)(n) = F(FIX(F))(n)

;; Non-anonymous recursive version of FACT
;; (fact 5) => 120
(defun fact (n)
  (if (zerop n)
    1
    (* n (fact (1- n)))))

;; Add FACT1 as its own argument
;; (fact1 #'fact1 5) => 120
(defun fact1 (fn n)
  (if (zerop n)
    1
    (* n (funcall fn fn (1- n)))))

;; Transforming from FACT1, construct FACT2 which accept "itself"
;; as argument, and return "itself".
;;
;; When N equals 0, FN will never be called.
;; No matter what type FN is, recursive will return.
;;
;; (funcall (fact2 (fact2 (fact2 (fact2 (fact2 (fact2 1)))))) 5) => 120
(defun fact2 (fn)
  #'(lambda (n)
      (if (zerop n)
        1
        (* n (funcall fn (1- n))))))

;; Construct fixed point function of FACT2.
;;
;; fix(F)(n) = F(fix(F))(n)
;;      (funcall (fix0 #'fact2) 5)
;;      equal => (funcall (fact2 (fix0 #'fact2)) 5)
;;
;; fn => (fn (fn (fn ...)))
;; fn => (fn (fix0 fn)))
;;
;; (funcall (fix1 #'fact2) 5)
(defun fix0 (fn)
  (funcall fn (lambda (&rest args)
                (apply (fix0 fn) args))))

(defun fix1 (fn)
  (labels ((fixed ()
             (funcall fn (lambda (&rest args)
                           (apply (fix1 fn) args)))))
    (fixed)))

(defun fix2 (fn)
  (labels ((fixed ()
             (funcall fn (lambda (&rest args)
                           (apply (fixed) args)))))
    (fixed)))
; (funcall (fix2 #'fact2) 5)

(defun fix3 (fn)
  (labels ((fixed (f)
             (funcall fn (lambda (&rest args)
                           (apply (fixed f) args)))))
    (fixed #'fixed)))

(defun fix4 (fn)
  (labels ((fixed (f)
             (funcall fn (lambda (&rest args)
                           (apply (funcall f f) args)))))
    (fixed #'fixed)))

;; Transform FIXED to anonymous lambda express:
;;  (lambda (func)
;;    (funcall func func))
(defun fix5 (fn)
  (funcall #'(lambda (func) (funcall func func))
           (lambda (f)
             (funcall fn (lambda (&rest args)
                           (apply (funcall f f) args))))))
; (funcall (fix5 #'fact2) 5)

(funcall ((lambda (fn)
            (funcall #'(lambda (func)
                         (funcall func func))
                     (lambda (f)
                       (funcall fn (lambda (&rest args)
                                     (apply (funcall f f) args))))))
          (lambda (fn)
            (lambda (n)
              (if (zerop n)
                1
                (* n (funcall fn (1- n)))))))
         5)

