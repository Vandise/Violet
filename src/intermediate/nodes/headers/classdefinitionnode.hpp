#ifndef __CLASSNODE_HPP__
#define __CLASSNODE_HPP__ 1

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
  class ClassDefinitionNode : public AbstractNode
  {
    private:
      std::string  name;
      std::string  superName;
      AbstractNode *body;

    public:
      ClassDefinitionNode(std::string name, std::string superName, AbstractNode *body);
      void compile(Context *context, Violet::Generator *generator);
  };
}

#endif