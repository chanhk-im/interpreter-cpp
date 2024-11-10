# RFAE in C++

> Course: Programming Language Theory  
> Section #: 02  
> Student #: 21900617  
> Name: 임찬혁

## Compile

``` bash
$ make main
```

## Execution

* Parser & Interpreter

``` bash
$ ./main "{fun {x} {with {y 5} {+ x y}}}"
(closureV x (app (fun y (add (id x) (id y))) (num 5)) (mtSub))
```

* Parser only  
You can execute this program to make only parsed code by using the option "-p".

``` bash
$ ./main -p "{fun {x} {with {y 5} {+ x y}}}"
(fun x (app (fun y (add (id x) (id y))) (num 5)))
```

## BNF

> \<RFAE> ::= \<num>  
> | {+ \<RFAE> \<RFAE>}  
> | {- \<RFAE> \<RFAE>}  
> | {* \<RFAE> \<RFAE>}  
> | \<id>  
> | {fun {\<id>} \<RFAE>}  
> | {\<RFAE> \<RFAE>}  
> | {if \<RFAE> \<RFAE> \<RFAE>}  
> | {or \<RFAE> \<RFAE>}  
> | {= \<RFAE> \<RFAE>}  
