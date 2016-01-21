#ifndef __LAMBDAOBJECT_HPP__
#define __LAMBDAOBJECT_HPP__ 1

#include "runtime/headers/object.hpp"
#include <string>
#include <vector>

class Context;

namespace Nodes
{
  class AbstractNode;
}
namespace Violet
{
  class Generator;
}
namespace Runtime
{
  class Object;
  class StdClass;

  class LambdaObject : public Object
  {
    private:
      Nodes::AbstractNode        *body;
      std::vector<std::string>   parameters;
      Context                    *context;
      Violet::Generator          *generator;
    public:
      LambdaObject(std::vector<std::string> parameters, Nodes::AbstractNode *body, Context *context, Violet::Generator *generator);
      Object* compile(std::vector<Runtime::Object*> arguments);
  };
}

#endif