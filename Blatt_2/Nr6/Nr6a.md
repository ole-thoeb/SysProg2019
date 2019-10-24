# Nr 6
## a)
### Parameter Übergabe
|Nummer|System V AMD64 ABI|Syscall|
|------|------------------|-------|
|1     |`RDI`             |`RDI`  |
|2     |`RSI`             |`RSI`  |
|3     |`RDX`             |`RDX`  |
|4     |`RCX`             |`R10`  |
|5     |`R8`              |`R8`   |
|6     |`R9`              |`R9`   |
|Rückgabe|`EAX`           |       |

### Unveränderte Register
Syscall: **alle** außer `RCX`, `R11` und `RAX` (Rückgabe)

System V AMD64 ABI: `rbx`, `rsp`, `rbp`, `r12-r15`