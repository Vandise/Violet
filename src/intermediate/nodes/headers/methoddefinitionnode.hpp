#ifndef __METHODDEFINITIONNODE_HPP__
#define __METHODDEFINITIONNODE_HPP__ 1

#include <string>
#include <map>
#include <vector>
#include "abstractnode.hpp"

class Context;

namespace Nodes
{
  class MethodDefinitionNode : public AbstractNode
  {
    private:
      std::string                name;
      AbstractNode               *body;
      std::vector<std::string>   parameters;

    public:
      MethodDefinitionNode(std::string name, std::vector<std::string> parameters, AbstractNode *body);
      void compile(Context *context, Violet::Generator *generator);
  };
}


#endif