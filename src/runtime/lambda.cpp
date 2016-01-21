#include "headers/lambda.hpp"
#include "intermediate/headers/context.hpp"
#include "runtime/headers/runtime.hpp"
#include "intermediate/nodes/headers/abstractnode.hpp"
#include "violet/headers/violetgenerator.hpp"
#include "violet/headers/violetvm.hpp"
#include <iostream>

Runtime::LambdaObject::LambdaObject(std::vector<std::string> parameters, Nodes::AbstractNode *body, Context *context, Violet::Generator *generator)
{
  this->klass = Lang::Runtime::getRootClass(std::string("Lambda"));
  this->parameters = parameters;
  this->body = body;
  this->context = context;
  this->generator = generator;
}

Runtime::Object*
Runtime::LambdaObject::compile(std::vector<Runtime::Object*> arguments)
{
  //
  // Lambda objects should preserve local variables in the given scope
  // Context *context = new Context(this);
  //

/*
  if(this->parameters.size() != arguments.size())
  {
    throw std::invalid_argument("Invalid argument count for method 'call' in object Lambda");
  }

  for(int i = 0; i < this->parameters.size(); i++)
  {
    this->context->setLocal(this->parameters[i], arguments[i]);
  }

  return this->body->eval(context);
*/

}