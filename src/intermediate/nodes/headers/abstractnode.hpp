#ifndef __ABSTRACTNODE_HPP__
#define __ABSTRACTNODE_HPP__ 1

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
  class AbstractNode
  {
    public:
      virtual void compile(Context *context, Violet::Generator *generator) = 0;
  };
}

#endif