#include <iostream>
#include <string>
#include "runtime/headers/method.hpp"
#include "runtime/headers/runtime.hpp"
#include "runtime/headers/valueobject.hpp"

struct IntAdd : Method
{
  Runtime::Object* call(Runtime::Object *receiver, std::vector<Runtime::Object*> arguments)
  {
    return new Runtime::ValueObject(
      boost::get<int>(receiver->getValue())
      +
      boost::get<int>(arguments[0]->getValue())
    );
  }
};

struct IntToFloat : Method
{
  Runtime::Object* call(Runtime::Object *receiver, std::vector<Runtime::Object*> arguments)
  {
    return new Runtime::ValueObject(
      static_cast< float >(boost::get<int>(receiver->getValue()))
    );
  }
};

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
IntAdd           int_add_overload_method;
IntMinusOp       int_subtract_method;
IntMultOp        int_multiply_method;
IntDivOp         int_divide_method;

IntLessThanOp    int_less_than_method;
IntGreaterThanOp int_greater_than_method;
IntEqualOp       int_equal_method;

IntToFloat       int_to_float_method;