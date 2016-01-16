#ifndef __CONTEXT_HPP__
#define __CONTEXT_HPP__ 1

#include <map>
#include <vector>
#include <string>

namespace Runtime
{
  class Object;
  class StdClass;
}

namespace FrontEnd
{
  class Driver;
}

class Context
{
  private:
    Runtime::Object        *currentSelf;
    Runtime::StdClass      *currentClass;
    Context                *parent;

  public:
    // [index, generator literal index]
    std::vector<int> local_bytes;
    std::vector<Runtime::Object*> locals;
    Context(Runtime::Object *currentSelf, Runtime::StdClass *currentClass, Context *parent);
    Context(Runtime::Object *currentSelf, Runtime::StdClass *currentClass);
    Context(Runtime::Object *currentSelf);
    Context();

    Runtime::Object*   getCurrentSelf();
    Runtime::StdClass* getCurrentClass();
    Runtime::Object*   getLocal(int index);
    int                hasLocal(int index);
    void               setLocal(int index, Runtime::Object *value);
    Context*           makeChildContext();
    void               compile(const char *filename);
    Runtime::Object*   eval(std::string code);
};

#endif

/*

  #include <boost/variant.hpp>
  [index, literal_index]
  std::vector< int > locals;


*/