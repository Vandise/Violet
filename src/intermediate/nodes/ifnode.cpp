#include "headers/ifnode.hpp"
#include "runtime/headers/runtime.hpp"
#include "intermediate/headers/context.hpp"
#include "runtime/headers/stdclass.hpp"
#include "violet/headers/violetgenerator.hpp"
#include <iostream>

Nodes::IfNode::IfNode(Nodes::AbstractNode *expressions, AbstractNode *body)
{
  this->expressions = expressions;
  this->body = body;
}

void
Nodes::IfNode::compile(Context *context, Violet::Generator *generator)
{
  this->expressions->compile(context, generator);
  generator->pushIf(this->expressions, this->body, context);
}