
#ifndef __COMPILEDMETHOD_HPP__
#define __COMPILEDMETHOD_HPP__ 1

#include <string>
#include <map>
#include <vector>
#include "method.hpp"

namespace Nodes
{
  class AbstractNode;
}

namespace Violet
{
  class Generator;
}

class CompiledMethod : public Method
{
  private:
    std::string                name;
    Nodes::AbstractNode        *body;
    std::vector<std::string>   parameters;
    Violet::Generator          *generator;

  public:
    CompiledMethod(std::string name, std::vector<std::string> parameters, Nodes::AbstractNode *body, Violet::Generator *generator);
    Runtime::Object* call(Runtime::Object *receiver, std::vector<Runtime::Object*> arguments);
};

#endif