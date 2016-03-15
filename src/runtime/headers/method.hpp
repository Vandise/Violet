#ifndef __METHOD_HPP__
#define __METHOD_HPP__ 1

#include <map>
#include <vector>
#include <string>
#include <iostream>
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

    std::string rec_class = receiver->getStdClass()->getName();
    std::transform(rec_class.begin(), rec_class.end(), rec_class.begin(), ::tolower);

    std::string arg_class = argument_object->getStdClass()->getName();
    std::transform(arg_class.begin(), arg_class.end(), arg_class.begin(), ::tolower);

    if(rec_class != arg_class)
    {
      if(argument_object->getStdClass()->hasMethod(std::string("to_")+rec_class))
      {
        argument_object = (Runtime::ValueObject*)(argument_object->call(std::string("to_")+rec_class, std::vector<Runtime::Object*>()));
      }
      else
      {
        throw std::invalid_argument(
          "\n No implicit conversion from class " + arg_class + " to class " + rec_class +
          ". Try casting reciever of class type " + rec_class + " to class type " + arg_class + ".\n"
        );
      }
    }

    T self     = boost::get<T>(((Runtime::ValueObject*)receiver)->getValue());
    T argument = boost::get<T>((argument_object)->getValue());
    return perform(self, argument, receiver->getStdClass()->getName(), argument_object->getStdClass()->getName());
  }

  virtual Runtime::Object* perform(T receiver, T argument, std::string receiver_class, std::string argument_class);
};

/*
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
*/

#endif