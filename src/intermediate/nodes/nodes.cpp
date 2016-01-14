#include <iostream>
#include "headers/nodes.hpp"
#include "runtime/headers/runtime.hpp"
#include "headers/abstractnode.hpp"
#include "intermediate/headers/context.hpp"
#include "runtime/headers/stdclass.hpp"
#include "violet/headers/violetgenerator.hpp"

Nodes::Nodes::Nodes(std::vector<AbstractNode*> nodes)
{
  this->nodes = nodes;
}

void
Nodes::Nodes::add(AbstractNode* node)
{
  this->nodes.push_back(node);
}

void
Nodes::Nodes::compile(Context *context, Violet::Generator *generator)
{
  //std::cout << "Total Nodes to eval: ";
  //std::cout << this->nodes.size();
  //std::cout << "\n";

  //Runtime::Object *lastEval = Lang::Runtime::nilObject;

  for (auto &n : this->nodes) {
    n->compile(context, generator);
  }

  //std::cout << "Returned Class: ";
  //std::cout << lastEval->getStdClass()->getName();
  //std::cout << "\n";
  //std::cout << "value: ";
  //std::cout << lastEval->getValue();
  //std::cout << "\n";

  //return lastEval;
}