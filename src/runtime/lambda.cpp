#include "headers/lambda.hpp"
#include "intermediate/headers/context.hpp"
#include "runtime/headers/runtime.hpp"
#include "intermediate/nodes/headers/abstractnode.hpp"
#include "violet/headers/violetgenerator.hpp"
#include "violet/headers/violetvm.hpp"
#include <iostream>

Runtime::LambdaObject::LambdaObject(std::vector<std::string> parameters, std::vector<int> instructions, int context, VioletVM *vm)
{
  this->klass = Lang::Runtime::getRootClass(std::string("Lambda"));
  this->parameters = parameters;
  this->instructions = instructions;
  this->vm = vm;
  this->context = context;
}

Runtime::Object*
Runtime::LambdaObject::compile(std::vector<Runtime::Object*> arguments)
{

  VioletVM lambda_vm;

  if(this->parameters.size() != arguments.size())
  {
    throw std::invalid_argument("Invalid argument count for method 'call' in object Lambda");
  }

  for(int i = parameters.size() - 1; i >= 0; i--)
  {
    lambda_vm.STACK_PUSH(arguments[i]);
  }

  Runtime::Object *currentSelf = this->vm->scopes[this->context]->getCurrentSelf();
  this->vm->scopes[this->context]->setCurrentSelf(this);
  lambda_vm.run(this->instructions, this->vm->literals, this->vm->scopes);
  this->vm->scopes[this->context]->setCurrentSelf(currentSelf);
  currentSelf = NULL;

  return lambda_vm.STACK_POP();

}