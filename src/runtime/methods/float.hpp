#include <iostream>
#include <string>
#include "runtime/headers/method.hpp"
#include "runtime/headers/runtime.hpp"
#include "runtime/headers/valueobject.hpp"

struct FloatEqualOp: OperatorMethod<float>
{
  Runtime::Object* perform(float receiver, float argument, std::string receiver_class, std::string argument_class)
  {
    return Lang::Runtime::toBoolean(receiver == argument);
  }
};

FloatEqualOp       float_equal_method;