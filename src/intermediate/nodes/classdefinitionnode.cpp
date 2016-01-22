#include "headers/classdefinitionnode.hpp"
#include "runtime/headers/runtime.hpp"
#include "intermediate/headers/context.hpp"
#include "runtime/headers/stdclass.hpp"
#include "violet/headers/violetgenerator.hpp"
#include "headers/nodes.hpp"
#include <iostream>

Nodes::ClassDefinitionNode::ClassDefinitionNode(std::string name, std::string superName, AbstractNode *body)
{
  this->name      = name;
  this->superName = superName;
  this->body      = (Nodes::Nodes*)body;
}

void
Nodes::ClassDefinitionNode::compile(Context *context, Violet::Generator *generator)
{
  Runtime::StdClass *klass;
  Nodes::Nodes *nodes = (Nodes::Nodes*)this->body;

  if(this->superName.empty())
  {
    if(context->getCurrentClass()->hasConstant(this->name))
    {
      klass = (Runtime::StdClass*)context->getCurrentClass()->getConstant(this->name);
    }
    else
    {
      klass = new Runtime::StdClass(this->name,
        (Runtime::StdClass*)context->getCurrentClass()->getConstant(std::string("Object"))
      );
    }
    klass->setStdClass(klass);
  }
  else
  {
    Runtime::StdClass *superClass = (Runtime::StdClass*)context->getCurrentClass()->getConstant(this->superName);
    superClass->setStdClass(superClass);
    klass = new Runtime::StdClass(this->name, superClass);
    klass->setStdClass(klass);
  }

  Context *class_context = new Context(klass, klass);

  generator->scopeIndex(class_context);

  for(int i = 0; i < nodes->nodes.size(); i++)
  {
    nodes->nodes[i]->compile(class_context, generator);
  }

  context->getCurrentClass()->setConstant(name, klass);

  generator->pushConstant(name, context);

}