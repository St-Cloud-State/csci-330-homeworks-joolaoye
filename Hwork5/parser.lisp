(defun terminal(term cur)
    (if (and (not (null cur)) (eql term (car cur)))
        (progn
            (setf cur (cdr cur))
            (format t "Current state: ~a~%" cur)
            cur
        )
        nil
    )
)

(defun G(cur)
    (let ((state cur))
        (cond
            ((setq cur (terminal 'x state))
                cur)
            ((setq cur (terminal 'y state))
                cur)
            ((setq cur (terminal 'z state))
                cur)
            ((setq cur (terminal 'w state))
                cur)
            (t
                nil)
        )
    )
)

(defun E_prime(cur)
    (let ((state cur))
        (let ((result (terminal 'o cur)))
            (if result
                (let ((result2 (G result)))
                    (if result2
                        (let ((result3 (E_prime result2)))
                            (if result3
                                result3
                                (progn
                                    state)))
                        (progn
                            state)))
                state))
    )
)

(defun E(cur)
    (let ((result (G cur)))
        (if result 
            (E_prime result)
            nil)
    )
)

(declaim (ftype (function (list) (or list null)) L_prime))

(defun L(cur)
    (let ((result (terminal 's cur)))
        (if result 
            (L_prime result)
            nil)
    )
)

(defun L_prime(cur)
    (let ((state cur))
        (let ((result (L cur)))
            (if result
                result
                state))
    )
)

(defun S_fun(cur)
    (let ((state cur))
        (let ((result (terminal 's cur)))
            (if result 
                result
                (let ((result (terminal 'd state)))
                    (if result
                        (let ((result (L result)))
                            (if result 
                                (terminal 'b result)
                                nil))
                        nil))))
    )
)

(defun I(cur)
    (let ((result (terminal 'i cur)))
        (if result
            (let ((result (E result)))
                (if result
                    (let ((result (S_fun result)))
                        (if result 
                            (I_prime result)
                            nil))
                    nil))
            nil)
    )
)

(defun I_prime(cur)
    (let ((state cur))
        (let ((result (terminal 'e cur)))
            (if result
                (S_fun result)
                nil))
    )
)

(defun parse(cur)
    (let ((result (I cur)))
        (if (and result (= 0 (length result)))
            t
            nil))
)
