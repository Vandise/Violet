#ifndef __DRIVER_HPP__
#define __DRIVER_HPP__ 1

#include <string>
#include <cstdint>
#include <vector>
#include "frontend/scanner.hpp"
#include "frontend/parser.tab.hpp"
#include "runtime/headers/valueobject.hpp"

class Context;

namespace Nodes
{
  class Nodes;
  class AbstractNode;
}

namespace Runtime
{
  class Object;
}

namespace FrontEnd
{

  class Driver
  {
    public:
       Driver() = default;
       virtual ~Driver();
       void parse( const char *filename );
       void push_stack(std::vector<Nodes::AbstractNode*> stack);
       void push_node(Nodes::AbstractNode *node);
       void execute(Context *context);

    private:
       FrontEnd::Parser  *parser  = nullptr;
       FrontEnd::Scanner *scanner = nullptr;
  };

}
#endif
