
(cl:in-package :asdf)

(defsystem "obstacle_recognizer-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "Information" :depends-on ("_package_Information"))
    (:file "_package_Information" :depends-on ("_package"))
  ))