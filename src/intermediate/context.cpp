#include <iostream>
#include <cstdlib>
#include "runtime/headers/runtime.hpp"
#include "runtime/headers/stdclass.hpp"
#include "headers/context.hpp"
#include "headers/driver.hpp"
#include "nodes/headers/nodes.hpp"


Context::Context(Runtime::Object *currentSelf, Runtime::StdClass *currentClass, Context *parent)
{
  this->currentSelf = currentSelf;
  this->currentClass = currentClass;
  this->parent = parent;
  this->locals = parent->locals;
}

Context::Context(Runtime::Object *currentSelf, Runtime::StdClass *currentClass)
{
  this->currentSelf = currentSelf;
  this->currentClass = currentClass;
  this->locals.clear();
}

Context::Context(Runtime::Object *currentSelf)
{
  this->currentSelf = currentSelf;
  this->currentClass = currentSelf->getStdClass();
}

Context::Context()
{
  this->currentSelf = Lang::Runtime::getMainObject();
  this->currentClass = currentSelf->getStdClass();
}

Runtime::Object*
Context::getCurrentSelf()
{
  return this->currentSelf;
}

Runtime::StdClass*
Context::getCurrentClass()
{
  return this->currentClass;
}

Runtime::Object*
Context::getLocal(std::string name)
{
  return this->locals[name];
}

int
Context::hasLocal(std::string name)
{
  if(this->locals.count(name) >= 1)
    return 1;
  return 0;
}

void
Context::setLocal(std::string name, Runtime::Object *value)
{
  this->locals[name] = value;
}

Context*
Context::makeChildContext()
{
  return new Context(this->currentSelf, this->currentClass, this);
}

Runtime::Object*
Context::eval(const char * const filename)
{
  FrontEnd::Driver driver;
  driver.parse( filename );
  return driver.execute(this);
}

Runtime::Object*
Context::eval(std::string code)
{
  
}