#include "headers/methoddefinitionnode.hpp"
#include "runtime/headers/compiledmethod.hpp"
#include "intermediate/headers/context.hpp"
#include "runtime/headers/stdclass.hpp"
#include "violet/headers/violetgenerator.hpp"
#include "runtime/headers/runtime.hpp"

#include <iostream>

Nodes::MethodDefinitionNode::MethodDefinitionNode(std::string name, std::vector<std::string> parameters, Nodes::AbstractNode *body)
{
  this->name = name;
  this->parameters = parameters;
  this->body = body;
}

void
Nodes::MethodDefinitionNode::compile(Context *context, Violet::Generator *generator)
{
  context->getCurrentClass()->addMethod(this->name,
    new CompiledMethod(this->name, this->parameters, this->body, generator)
  );
}