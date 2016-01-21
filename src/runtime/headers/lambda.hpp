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
      std::vector<int>           instructions;
      std::vector<std::string>   parameters;
      Context                    *context;
    public:
      LambdaObject(std::vector<std::string> parameters, std::vector<int> instructions, Context *context);
      Object* compile(std::vector<Runtime::Object*> arguments);
  };
}

#endif