#include <iostream>
#include <cstdlib>
#include <vector>
#include "headers/bootstrapper.hpp"
#include  "intermediate/headers/context.hpp"
#include "headers/stdclass.hpp"
#include "methods/methods.hpp"

Context*
Bootstrapper::run()
{
  Runtime::StdClass *classClass = new Runtime::StdClass("Class");
  Runtime::StdClass *objectClass = new Runtime::StdClass("Object", classClass);
  Lang::Runtime::objectClass = objectClass;

  Runtime::Object *main = new Runtime::Object();
  Lang::Runtime::mainObject = main;

  objectClass->setStdClass(objectClass); // object is a class
  classClass->setStdClass(classClass); // class is a class
  main->setStdClass(objectClass);

  objectClass->setConstant("Object", objectClass); // woo recursion! 
  objectClass->setConstant("Class", classClass);

  Lang::Runtime::nilObject    = objectClass->newSubclass(std::string("NilClass"))->newInstance(0);
  Lang::Runtime::trueObject   = objectClass->newSubclass(std::string("TrueClass"))->newInstance(1);
  Lang::Runtime::falseObject  = objectClass->newSubclass(std::string("FalseClass"))->newInstance(0);
  Runtime::StdClass *intClass = objectClass->newSubclass(std::string("Integer"));
  Runtime::StdClass *strClass = objectClass->newSubclass(std::string("String"));
  Runtime::StdClass *floatClass = objectClass->newSubclass(std::string("Float"));

  Runtime::StdClass *lambdaClass = objectClass->newSubclass(std::string("Lambda"));

  objectClass->addMethod(std::string("print"),&object_print_method);

  return new Context(main);
}