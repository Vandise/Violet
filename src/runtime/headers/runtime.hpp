#ifndef __RUNTIME_HPP__
#define __RUNTIME_HPP__ 1

#include <string>

namespace Runtime
{
  class Object;
  class StdClass;
}

namespace Lang
{
  class Runtime
  {
    public:
      static ::Runtime::StdClass* objectClass;
      static ::Runtime::Object*   mainObject;
      static ::Runtime::Object*   nilObject;
      static ::Runtime::Object*   trueObject;
      static ::Runtime::Object*   falseObject;

      static ::Runtime::StdClass* getObjectClass();
      static ::Runtime::Object* getMainObject();
      static ::Runtime::StdClass* getRootClass(std::string name);
      static ::Runtime::StdClass* getExceptionClass();
      static ::Runtime::Object* getNil();
      static ::Runtime::Object* getTrue();
      static ::Runtime::Object* getFalse();
      static ::Runtime::Object* toBoolean(int value);
  };

}

#endif