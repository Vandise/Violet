#ifndef __NODESTACK_HPP__
#define __NODESTACK_HPP__ 1

#include <vector>

namespace Nodes
{
  class AbstractNode;
}

class NodeStack
{
  public:
    static std::vector<Nodes::AbstractNode*> stack;
};

#endif