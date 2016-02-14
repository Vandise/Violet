#include "headers/returnnode.hpp"
#include "runtime/headers/runtime.hpp"
#include "intermediate/headers/context.hpp"
#include "runtime/headers/stdclass.hpp"
#include "violet/headers/violetgenerator.hpp"
#include <iostream>

Nodes::ReturnNode::ReturnNode(AbstractNode *expressions)
{
  this->expressions = expressions;
}

void
Nodes::ReturnNode::compile(Context *context, Violet::Generator *generator)
{
  this->expressions->compile(context, generator);
  generator->emitReturn();
}