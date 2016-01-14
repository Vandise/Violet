#ifndef __LITERALNODE_HPP__
#define __LITERALNODE_HPP__ 1

#include <string>
#include <vector>
#include <boost/variant/get.hpp>
#include <boost/variant.hpp>
#include "abstractnode.hpp"
#include "runtime/headers/valueobject.hpp"

class Context;

namespace Runtime
{
  class ValueObject;
}

namespace Violet
{
  class Generator;
}

namespace Nodes
{
  class LiteralNode : public AbstractNode
  {
    public:
      boost::variant<int,float,std::string> value;
      LiteralNode(boost::variant<int,float,std::string> value);
      void compile(Context *context, Violet::Generator *generator);
  };
}

#endif