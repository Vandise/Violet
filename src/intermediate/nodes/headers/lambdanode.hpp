#ifndef __LAMBDANODE_HPP__
#define __LAMBDANODE_HPP__ 1

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
  class LambdaNode : public AbstractNode
  {
    private:
      AbstractNode               *body;
      std::vector<std::string>   parameters;

    public:
      LambdaNode(std::vector<std::string> parameters, AbstractNode *body);
      void compile(Context *context, Violet::Generator *generator);
  };
}

#endif