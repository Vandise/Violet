#ifndef __LOCALASSIGNNODE_HPP__
#define __LOCALASSIGNNODE_HPP__ 1

#include <string>
#include "abstractnode.hpp"

class Context;

namespace Nodes
{
  class LocalAssignNode : public AbstractNode
  {
    private:
      std::string name;
      AbstractNode *expression;

    public:
      LocalAssignNode(std::string name, AbstractNode *expression);
      void compile(Context *context, Violet::Generator *generator);
  };
}

#endif