#ifndef __CALLNODE_HPP__
#define __CALLNODE_HPP__ 1

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
  class CallNode : public AbstractNode
  {
    private:
      AbstractNode *receiver;
      std::string  method;
      std::vector<AbstractNode*> arguments;

    public:
      CallNode(std::string method, AbstractNode *receiver, std::vector<AbstractNode*> arguments);
      void compile(Context *context, Violet::Generator *generator);
  };
}

#endif