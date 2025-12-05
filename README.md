tclisp: small (50 lines) lisp-like interpreter

- c version: with tons of memory leaks
- c++ version: without memory leaks


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

