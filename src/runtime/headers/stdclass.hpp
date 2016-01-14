#ifndef __STDCLASS_HPP__
#define __STDCLASS_HPP__ 1

#include <string>
#include <map>

#include "object.hpp"

struct Method;

namespace Runtime
{
  class Object;
  class StdClass : public Object
  {
    private:
      typedef Object super;
      std::string name;
      std::map<std::string, Object*> constants;
      std::map<std::string, Method*> methods;
      StdClass *superClass;

    public:
      StdClass(std::string name, StdClass *superClass);
      StdClass(std::string name);
      std::string getName();
      StdClass* getSuperClass();
      void     setConstant(std::string name, Object *value);
      Object*  getConstant(std::string name);
      int      hasConstant(std::string name);
      Method*  lookup(std::string name);
      int      hasMethod(std::string name);
      void     addMethod(std::string name, Method *method);
      Object*  newInstance(int value);
      Object*  newInstance();
      StdClass* newSubclass(std::string name);
      StdClass* subclass(std::string name);
      int       isSubclass(StdClass *klass);
      int       equals(std::string other);
  };

}

#endif