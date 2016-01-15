#include "headers/localassignnode.hpp"
#include "intermediate/headers/context.hpp"
#include "runtime/headers/object.hpp"
#include "violet/headers/violetgenerator.hpp"

Nodes::LocalAssignNode::LocalAssignNode(std::string name, Nodes::AbstractNode *expression)
{
  this->name = name;
  this->expression = expression;
}

void
Nodes::LocalAssignNode::compile(Context *context, Violet::Generator *generator)
{
  // push a value onto the stack
  this->expression->compile(context, generator);

  // register the local value in the context
  generator->setLocal(this->name, context);
}