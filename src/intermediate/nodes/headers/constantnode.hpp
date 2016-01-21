#ifndef __CONSTANTNODE_HPP__
#define __CONSTANTNODE_HPP__ 1

#include <string>
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
  class ConstantNode : public AbstractNode
  {
    private:
      std::string name;

    public:
      ConstantNode(std::string name);
      void compile(Context *context, Violet::Generator *generator);
  };
}

#endif