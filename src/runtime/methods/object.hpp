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

struct ObjectSend : Method
{
  Runtime::Object* call(Runtime::Object *receiver, std::vector<Runtime::Object*> arguments)
  {
    std::string method = boost::get<std::string>(arguments[0]->getValue());
    arguments.erase(arguments.begin());
    return receiver->call(method, arguments);
  }
};

ObjectPrint         object_print_method;
ObjectSend          object_send_method;