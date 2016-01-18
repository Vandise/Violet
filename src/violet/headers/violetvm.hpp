#ifndef __VIOLETVM_HPP__
#define __VIOLETVM_HPP__ 1

#include <vector>
#include <string>
#include <boost/variant.hpp>
#include <boost/variant/get.hpp>

#define STACK_MAX   500

class Context;

namespace Runtime
{
  class Object;
  class StdClass;
}

class VioletVM
{
  private:
    std::vector<Runtime::Object*> stack;

  public:
    void run(std::vector<int> instructions, std::vector< boost::variant<int,float,std::string> > literals, std::vector<Context*> scopes);
    void STACK_PUSH(Runtime::Object* object);
    Runtime::Object* STACK_POP();
};

#endif