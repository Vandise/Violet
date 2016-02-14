#ifndef __RETURNNODE_HPP__
#define __RETURNNODE_HPP__ 1

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
  class ReturnNode : public AbstractNode
  {
    private:
      Nodes::AbstractNode        *expressions;

    public:
      ReturnNode(AbstractNode *expressions);
      void compile(Context *context, Violet::Generator *generator);
  };
}

#endif