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
    //Runtime::Object*   getLocal(std::string name);
    //int                hasLocal(std::string name);
    //void               setLocal(std::string name, Runtime::Object *value);
    Context*           makeChildContext();
    Runtime::Object*   eval(const char *filename);
    Runtime::Object*   eval(std::string code);
};

#endif

/*

  #include <boost/variant.hpp>
  [index, literal_index]
  std::vector< int > locals;


*/