#ifndef __IFNODE_HPP__
#define __IFNODE_HPP__ 1

#include <string>
#include <map>
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
  class IfNode : public AbstractNode
  {
    private:
      AbstractNode               *body;
      Nodes::AbstractNode        *expressions;

    public:
      IfNode(Nodes::AbstractNode *expressions, AbstractNode *body);
      void compile(Context *context, Violet::Generator *generator);
  };
}

#endif