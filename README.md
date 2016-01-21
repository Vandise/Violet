# Violet
Violet Virtual Machine

## Violet Instruction Set

Opcode        | Operand 1     | Operand 2     | Operand 3     | Operand 4
------------- | ------------- | ------------- | ------------- | -------------
CALL          | arg_count     |
PUSH_INTEGER  | literal_index | 
PUSH_FLOAT    | literal_index |
PUSH_STRING   | literal_index |
PUSH_ARRAY    | N/I           |
PUSH_HASH     | N/I           |
PUSH_LAMBDA   | N/I           |
PUSH_OBJECT   | literal_name  | scope_index   | 
PUSH_SELF     | scope_index   |
GET_LOCAL     | local_index   | scope_index   |
SET_LOCAL     | local_index   | scope_index   |
RETURN        |

N/I = Not Yet Implemented and subject to change or be removed

## Stack

Opcode        | Before                              | After    
------------- | ----------------------------------- | ----------------------------------- |
CALL          | [arg1,arg2..,receiver,method]       | [returned]
PUSH_INTEGER  | []                                  | [integer]
PUSH_FLOAT    | []                                  | [float]
PUSH_STRING   | []                                  | [string]
PUSH_ARRAY    | N/I                                 |
PUSH_HASH     | N/I                                 |
PUSH_LAMBDA   | N/I                                 |
PUSH_OBJECT   | []                                  | [object]
PUSH_SELF     | []                                  | [self]
GET_LOCAL     | []                                  | [object]
SET_LOCAL     | []                                  | []
RETURN        | []                                  | []

## Azalea Language
Azalea comes default with the Violet Virtual Machine. Azalea treats everything as an object as per specifications in the VioletVM. Even primitive datatypes such as integers, floats, and strings(character arrays) are objects.

### Comments
```
// this is a comment
```

### Assignment
``` 
IDENTIFIER = EXPRESSION 
x = 10
```
### Method Definitions
```
func IDENTIFIER(arguments)
  expressions
end

func return_string(string)
  string
end
```

### Calling Methods
```
IDENTIFIER(arguments)
print("Hello World)

expressions.IDENTIFIER(arguments)
self.print("Hello World")
```

### Lambda
There's a bug with lambda expressions that defines the parameter in the current scope -- which will override any local variables with the same name. It's on my todo list.
```
-> do |arguments|
  expressions
end

(-> do |greeting|
  print(greeting)
end).call("Hello World")

callable = -> do |hello|
  print(hello)
end

callable.call("Hello")
```
