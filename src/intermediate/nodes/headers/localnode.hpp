#ifndef __LOCALNODE_HPP__
#define __LOCALNODE_HPP__ 1

#include <string>
#include "abstractnode.hpp"

class Context;

namespace Nodes
{
  class LocalNode : public AbstractNode
  {
    private:
      std::string name;

    public:
      LocalNode(std::string name);
      void compile(Context *context, Violet::Generator *generator);
  };
}

#endif