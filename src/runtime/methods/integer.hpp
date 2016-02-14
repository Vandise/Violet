#include <iostream>
#include <string>
#include "runtime/headers/method.hpp"
#include "runtime/headers/runtime.hpp"
#include "runtime/headers/valueobject.hpp"

struct IntAddOp: OperatorMethod<int>
{
  Runtime::Object* perform(int receiver, int argument, std::string receiver_class, std::string argument_class)
  {
    return new Runtime::ValueObject(receiver + argument);
  }
};

struct IntMinusOp: OperatorMethod<int>
{
  Runtime::Object* perform(int receiver, int argument, std::string receiver_class, std::string argument_class)
  {
    return new Runtime::ValueObject(receiver - argument);
  }
};

struct IntMultOp: OperatorMethod<int>
{
  Runtime::Object* perform(int receiver, int argument, std::string receiver_class, std::string argument_class)
  {
    return new Runtime::ValueObject(receiver * argument);
  }
};

struct IntDivOp: OperatorMethod<int>
{
  Runtime::Object* perform(int receiver, int argument, std::string receiver_class, std::string argument_class)
  {
    return new Runtime::ValueObject(receiver / argument);
  }
};

struct IntLessThanOp: OperatorMethod<int>
{
  Runtime::Object* perform(int receiver, int argument, std::string receiver_class, std::string argument_class)
  {
    return Lang::Runtime::toBoolean(receiver < argument);
  }
};

struct IntGreaterThanOp: OperatorMethod<int>
{
  Runtime::Object* perform(int receiver, int argument, std::string receiver_class, std::string argument_class)
  {
    return Lang::Runtime::toBoolean(receiver > argument);
  }
};

struct IntEqualOp: OperatorMethod<int>
{
  Runtime::Object* perform(int receiver, int argument, std::string receiver_class, std::string argument_class)
  {
    return Lang::Runtime::toBoolean(receiver == argument);
  }
};

IntAddOp         int_add_method;
IntMinusOp       int_subtract_method;
IntMultOp        int_multiply_method;
IntDivOp         int_divide_method;

IntLessThanOp    int_less_than_method;
IntGreaterThanOp int_greater_than_method;
IntEqualOp       int_equal_method;