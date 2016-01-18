#include <iostream>
#include <string>
#include "runtime/headers/method.hpp"
#include "runtime/headers/runtime.hpp"
#include "runtime/headers/valueobject.hpp"

struct ObjectPrint : Method
{
  Runtime::Object* call(Runtime::Object *receiver, std::vector<Runtime::Object*> arguments)
  {
    for(int i = 0; i < arguments.size(); i++)
    {
      std::cout << arguments[i]->getValue() << std::endl;
    }
    return Lang::Runtime::getNil();
  }
};

ObjectPrint         object_print_method;