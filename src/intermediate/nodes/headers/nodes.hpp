#ifndef __NODES_HPP__
#define __NODES_HPP__ 1

#include <vector>
#include "abstractnode.hpp"

class Context;

namespace Runtime
{
  class Object;
}

namespace Violet
{
  class Generator;
}

namespace Nodes
{
  class AbstractNode;
  class Nodes : public AbstractNode
  {
    public:
      std::vector<AbstractNode*> nodes;
      Violet::Generator          *generator;
    public:
      Nodes(std::vector<AbstractNode*> nodes);
      void add(AbstractNode* node);
      void compile(Context *context, Violet::Generator *generator);
      void execute();
  };
}

#endif