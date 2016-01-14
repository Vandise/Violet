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
  /*
  if(receiver == NULL && arguments.empty() && context->hasLocal(method))
  {
    //return context->getLocal(method);
  }

  Runtime::Object* evaledReceiver;
  if(receiver == NULL)
  {
    evaledReceiver = context->getCurrentSelf();
  }
  else
  {
    evaledReceiver = receiver->compile(context);
  }

  std::vector<Runtime::Object*> evalArguments;

  for(int i = 0; i < this->arguments.size(); i++)
  {
    Runtime::Object *evalArg = (this->arguments[i])->compile(context);
    evalArguments.push_back(evalArg);
  }
  */
  //Runtime::Object *evalReciever = this->receiver->eval(context);
  //return evaledReceiver->call(this->method, evalArguments);
}