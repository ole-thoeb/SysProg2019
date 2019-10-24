# Blatt 1

## Aufgabe 4

### a

`i` wird in jedem Schleifendurchgang überschrieben. Am ende wird nur eine speicherstelle gefreed, es wurden aber 10 allociert -> 9 memory leaks

### b
`d[2]` greift auf unallocierten Speicher zu, da Arrays 0 indeziert sind.

### c
worauf `*i` ist undefiniert, da es nie gesetzt wurde. `**i = 5;` schreibt also `5` an eine undefinierte Stelle im Speicher