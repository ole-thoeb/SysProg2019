`indent -br -ce -brs -bap -i4 -lp -ts4 -npsl -npcs -ss -sob -brf <input-file> -o <output-file>`

`indent -br -ce -brs -bap -i4 -lp -ts4 -npsl -npcs -ss -sob -brf <input-files>`

|option|description|
|------|-----------|
|-br   |braces on same line as `if`|
|-ce   |Cuddle `else` and preceding `}`|
|-bap  |blank line after procedure|
|-brs  |Put braces on `struct` declaration line|
|-npsl |Put the type of a procedure on the same line as its name|
|-npcs |Do not put space after the function in function calls|
|-ss   |On one-line `for` and `while` statements, force a blank before the semicolon|
|-sob  |Swallow optional blank lines|
|-brf|Put braces on function definition line|
|-i4|Set indentation level to 4 spaces|
|-lp|Line up continued lines at parentheses|
|-ts4|Set tab size to 4 spaces|
