- abbruchbedingung

enter: rettet `bsp` auf stack und setzt `bsp = rsp`
``` assembly
push bsp 
mov bsp, rsp
```
leave: setzt `rsp = bsp` und holt den alten `rsp` vom stack
``` assembly
mov rsp, bsp 
pop rbp
```