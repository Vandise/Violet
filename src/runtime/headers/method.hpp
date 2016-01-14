#ifndef __METHOD_HPP__
#define __METHOD_HPP__ 1

#include <map>
#include <vector>
#include <string>
#include <stdexcept>
#include "stdclass.hpp"
#include "valueobject.hpp"
#include <boost/variant/get.hpp>

namespace Runtime
{
  class Object;
  class ValueObject;
}

struct Method
{
  virtual Runtime::Object* call(Runtime::Object *receiver, std::vector<Runtime::Object*> arguments) = 0;
};

template<typename T>
struct OperatorMethod : Method
{
  Runtime::Object* call(Runtime::Object *receiver, std::vector<Runtime::Object*> arguments)
  {
    Runtime::ValueObject* argument_object = (Runtime::ValueObject*)arguments[0];
    std::string class_name = argument_object->getStdClass()->getName();
    
    if(class_name != std::string("Integer"))
    {
      throw std::invalid_argument("No valid conversion from class "+class_name+" class Integer\n");
    }
    
    T self     = boost::get<T>(((Runtime::ValueObject*)receiver)->getValue());
    T argument = boost::get<T>((argument_object)->getValue());
    return perform(self, argument);
  }

  virtual Runtime::Object* perform(T receiver, T argument);
};

template<typename S, typename I>
struct StringOperatorMethod : Method
{
  Runtime::Object* call(Runtime::Object *receiver, std::vector<Runtime::Object*> arguments)
  {
    S self     = boost::get<S>(((Runtime::ValueObject*)receiver)->getValue());
    I argument = boost::get<I>(((Runtime::ValueObject*)arguments[0])->getValue());
    return perform(self, argument);
  }

  virtual Runtime::Object* perform(S receiver, I argument);
};

#endif