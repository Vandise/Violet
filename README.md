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
PUSH_LAMBDA   | params        | lambda_body   | parent_scope  |
PUSH_OBJECT   | literal_name  | scope_index   | 
PUSH_SELF     | scope_index   |
GET_LOCAL     | local_index   | scope_index   |
SET_LOCAL     | local_index   | scope_index   |
JUMP_UNLESS   | inst_count    |
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
PUSH_LAMBDA   | []                                  | [lambda_object]
PUSH_OBJECT   | []                                  | [object]
PUSH_SELF     | []                                  | [self]
GET_LOCAL     | []                                  | [object]
SET_LOCAL     | []                                  | []
JUMP_UNLESS   | [bool_obj]                          | []
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
The lambda body is executed within a child scope, meaning it has access to parent variables.
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

// parent variable example
outside_int = 10
lambda = -> do |param_int| 
  outside_int = param_int
end

lambda.call(5)
print(outside_int)
=> 5
```

### Class Definitions
```
class CONSTANT
  Expressions
END

class CONSTANT : CONSTANT
  Expressions
END

class Person
  func say_something(words)
    print(words)
  end
end

Person.say_something("Hello")
=> Hello
```
### Operators
Operators are methods and can be overloaded by the "operator" declaration. Every operator method accepts one argument.
```
// operators: + - * / > < >= <= ==

class User
  operator ==(argument)
    print("Called == on User Object, passed argument: ", argument)
  end
end

User == 10
=> Called == on User Object, passed argument: 10
```

#### Overloading operators in core objects
Ever want to prove to your friend that 1 + 1 = 4? Here's how you would do it in Azalea:
```
class Integer
  operator +(int)
    ret self.add(int).add(2)
  end
end

print(1 + 1)
=> 4
```

### Conditionals and control structures

#### IF
```
// if statement
IF conditions
  expressions
end

if 10 == 5
  print("They are equal")
end
print("Completed)
=> "Completed"
```

#### RETURN (ret)
Pushes a value to the stack and exits the current scope.
```
y = ((-> do |n|
  if n == 2
    ret "iterated to 2"
  end
  print("Adding 1")
  self.call(n+1)
end).call(0))

print("The value of y is", y)

=> "Adding 1"
=> "Adding 1"
=> "The value of y is" "iterated to 2" 
```
