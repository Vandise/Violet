#include <sstream>
#include "headers/object.hpp"
#include "headers/runtime.hpp"
#include "headers/stdclass.hpp"
#include "headers/method.hpp"

Runtime::Object::Object()
{
  /* TODO */
}

Runtime::Object::Object(Runtime::StdClass *klass)
{
  this->klass = klass;
}

/*
  Not yet implemented, this is the "super()" method that will make
  the super class of a ValueObject. ie
  
  ValueObject(int value)
    super("Integer")
  
  Integer will be a subclass of Object and instantiated in the runtime.
  That way we can add methods to numbers and strings without creating different
  nodes other than the current literal node.
  
*/
Runtime::Object::Object(std::string name)
{
  this->klass = Lang::Runtime::getRootClass(name);
}

Runtime::StdClass*
Runtime::Object::getStdClass()
{
  return this->klass;
}

void
Runtime::Object::setStdClass(Runtime::StdClass *stdClass)
{
  this->klass = stdClass;
}

Runtime::Object*
Runtime::Object::getInstanceVariable(std::string name)
{
  if(hasInstanceVariable(name))
    return instanceVariables[name];
  return Lang::Runtime::getNil();
}

int
Runtime::Object::hasInstanceVariable(std::string name)
{
  return instanceVariables.count(name);
}

void
Runtime::Object::setInstanceVariable(std::string name, Runtime::Object *value)
{
  instanceVariables[name] = value;
}

Runtime::Object*
Runtime::Object::call(std::string method, std::vector<Runtime::Object*> arguments)
{
  return klass->lookup(method)->call(this, arguments);
}

Runtime::Object*
Runtime::Object::call(std::string method)
{
  /* TODO */
}


int
Runtime::Object::isTrue()
{
  return 1;
}

int
Runtime::Object::isFalse()
{
  return 0;
}

int
Runtime::Object::isNil()
{
  return 0;
}

//
// Future Node:
// Get Value should probably allow Object returns as well.
// GetValue() currently is just used to evaluate and object and its value
// maybe change to a toString() method.
//
boost::variant<int,float,std::string>
Runtime::Object::getValue()
{
  const void * address = static_cast<const void*>(this);
  std::stringstream ss;
  ss << address;
  std::string addr = ss.str();
  return std::string("<"+getName()+" "+addr+">");
}


std::string
Runtime::Object::getName()
{
  if(this->klass)
    return this->klass->getName();

  return std::string("Object");
}