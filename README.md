tclisp: small (50 lines of C) lisp-like interpreter with tons of memory leaks.

It's tcl + lisp

```clojure
(repeat 10 (do
  (print 'hi')
  (print (add 1 2 3 4 5))
))
```

```
hi
15
hi
15
hi
15
hi
15
hi
15
hi
15
hi
15
hi
15
hi
15
hi
15
```

