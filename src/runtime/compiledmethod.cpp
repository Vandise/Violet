#include "headers/stdclass.hpp"
#include "headers/compiledmethod.hpp"
#include "intermediate/nodes/headers/abstractnode.hpp"
#include "intermediate/headers/context.hpp"
#include "violet/headers/violetgenerator.hpp"
#include "violet/headers/violetvm.hpp"
#include <stdexcept>
#include <iostream>

CompiledMethod::CompiledMethod(std::string name, std::vector<std::string> parameters, Nodes::AbstractNode *body, Violet::Generator *generator)
{
  this->name = name;
  this->parameters = parameters;
  this->body = body;
  this->generator = generator;
}

Runtime::Object*
CompiledMethod::call(Runtime::Object *receiver, std::vector<Runtime::Object*> arguments)
{

  Violet::Generator generator;
  VioletVM          vm;

  Context *context = new Context(receiver);

  if(parameters.size() != arguments.size())
  {
    throw std::invalid_argument("Invalid argument count for method " + this->name);
  }

  for(int i = 0; i < parameters.size(); i++)
  {
    vm.STACK_PUSH(arguments[i]);
  }

  for(int i = parameters.size() - 1; i >= 0; i--)
  {
    generator.setLocal(parameters[i], context);
  }

  this->body->compile(context, &generator);

  generator.assemble();
  vm.run(generator.instructions, generator.literals, generator.scopes);

  return vm.STACK_POP();

}