#include "headers/lambdanode.hpp"
#include "runtime/headers/runtime.hpp"
#include "intermediate/headers/context.hpp"
#include "runtime/headers/stdclass.hpp"
#include "runtime/headers/lambda.hpp"
#include "violet/headers/violetgenerator.hpp"
#include <iostream>

Nodes::LambdaNode::LambdaNode(std::vector<std::string> parameters, Nodes::AbstractNode *body)
{
  this->parameters = parameters;
  this->body = body;
}

void
Nodes::LambdaNode::compile(Context *context, Violet::Generator *generator)
{
  generator->pushLambda(this->parameters, this->body, context);
}