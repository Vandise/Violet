#include "headers/stdclass.hpp"
#include "headers/valueobject.hpp"
#include "headers/runtime.hpp"
#include "headers/method.hpp"
#include <stdexcept>
#include <iostream>

Runtime::StdClass::StdClass(std::string name)
{
  this->name = name;
  this->superClass = Lang::Runtime::getObjectClass();
  this->klass = Lang::Runtime::getObjectClass();
}

Runtime::StdClass::StdClass(std::string name, Runtime::StdClass *superClass)
{
  this->name = name;
  this->superClass = superClass;
  this->klass = Lang::Runtime::getObjectClass();
}

std::string
Runtime::StdClass::getName()
{
  return name;
}

void
Runtime::StdClass::setConstant(std::string name, Runtime::Object *value)
{
  constants[name] = value;
}

Runtime::StdClass*
Runtime::StdClass::getSuperClass()
{
  return superClass;
}

Runtime::Object*
Runtime::StdClass::getConstant(std::string name)
{
  if(constants.count(name) >= 1)
    return constants[name];
  if(superClass)
    return superClass->getConstant(name);
  return Lang::Runtime::getNil();
}

int
Runtime::StdClass::hasConstant(std::string name)
{
  if(constants.count(name) >= 1)
    return 1;
  if(superClass)
    return superClass->hasConstant(name);
  return 0;
}

Method*
Runtime::StdClass::lookup(std::string name)
{
  if(methods.count(name) >= 1)
  {
    return methods[name];
  }
  if(superClass)
  {
    return superClass->lookup(name);
  }
  throw std::invalid_argument("Call to undefined method.\n");
}

int
Runtime::StdClass::hasMethod(std::string name)
{
  if(methods.count(name) >= 1)
    return 1;
  if(superClass)
    return superClass->hasMethod(name);
  return 0;
}

void
Runtime::StdClass::addMethod(std::string name, Method *method)
{
  methods[name] = method;
}

Runtime::Object*
Runtime::StdClass::newInstance()
{
  return new Runtime::Object(this);
}

Runtime::Object*
Runtime::StdClass::newInstance(int value)
{
  return new Runtime::ValueObject(this, value);
}

Runtime::StdClass*
Runtime::StdClass::newSubclass(std::string name)
{
  Runtime::StdClass *klass = new Runtime::StdClass(name, this);
  Lang::Runtime::getObjectClass()->setConstant(name, klass);
  return klass;
}

Runtime::StdClass*
Runtime::StdClass::subclass(std::string name)
{
  Runtime::StdClass *objClass = Lang::Runtime::getObjectClass();
  if(objClass->hasConstant(name))
    return static_cast<Runtime::StdClass*>(objClass->getConstant(name));
  return newSubclass(name);
}

int
Runtime::StdClass::isSubclass(Runtime::StdClass *klass)
{
  if(klass == this)                  return 1;
  if(klass->getSuperClass() == 0)    return 0;
  if(klass->getSuperClass() == this) return 1;
  return isSubclass(klass->getSuperClass());
}

int
Runtime::StdClass::equals(std::string other)
{
  /* TODO */
}