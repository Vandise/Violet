#include "headers/callnode.hpp"
#include "runtime/headers/stdclass.hpp"
#include "intermediate/headers/context.hpp"
#include "violet/headers/violetgenerator.hpp"
#include <iostream>

Nodes::CallNode::CallNode(std::string method, AbstractNode *receiver, std::vector<AbstractNode*> arguments)
{
  this->method = method;
  this->receiver = receiver;
  this->arguments = arguments;
}

void
Nodes::CallNode::compile(Context *context, Violet::Generator *generator)
{
  // push all the arguments onto the stack
  for(int i = 0; i < this->arguments.size(); i++)
  {
    this->arguments[i]->compile(context, generator);
  }

  // push the receiver onto the stack
  if(this->receiver == NULL)
  {
    //PUSH_SELF [context]
    generator->selfLiteral(context);
  }
  else
  {
    // TODO:
    //  PUSH_CONSTANT [constant, context]
    //  this->receiver->compile(context, generator);
  }

  // push the method onto the stack
  //generator->emitByte(generator->literalIndex(this->method));
  generator->stringLiteral(this->method);

  // final stack:
  //  args...
  //  receiver
  //  method
  //  CALL
  //  argc
  generator->callMethod(this->arguments.size());
}