# Violet
Violet Virtual Machine

## Violet Instruction Set Example:
```Violet
x = “Hello World”
print(x)
——
[3 0] [17 0 0] [16 0 0] [7 0] [3 2] [0 1] [21]
——
[3 0]
PUSH_STRING    at literal index 0
[17 0 0] 
SET_LOCAL      at index 0 in scope 0
[16 0 0] 
GET_LOCAL      at index 0 in scope 0
[7 0]
PUSH_SELF      at current scope 0
[3 2]
PUSH_STRING    at literal index 2 #method name, TBD.
[0 1]
CALL           method with 1 argument
[21]
RETURN
```


