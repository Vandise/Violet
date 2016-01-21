#include "headers/constantnode.hpp"
#include "runtime/headers/stdclass.hpp"
#include "intermediate/headers/context.hpp"
#include "violet/headers/violetgenerator.hpp"
#include <iostream>

Nodes::ConstantNode::ConstantNode(std::string name)
{
  this->name = name;
}

void
Nodes::ConstantNode::compile(Context *context, Violet::Generator *generator)
{
  generator->pushConstant(this->name, context);
}