#include "headers/localnode.hpp"
#include "intermediate/headers/context.hpp"
#include "runtime/headers/object.hpp"
#include "violet/headers/violetgenerator.hpp"

Nodes::LocalNode::LocalNode(std::string name)
{
  this->name = name;
}

void
Nodes::LocalNode::compile(Context *context, Violet::Generator *generator)
{
  generator->getLocal(this->name, context);
}