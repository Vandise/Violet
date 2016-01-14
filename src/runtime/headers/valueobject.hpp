#ifndef __VALUEOBJECT_HPP__
#define __VALUEOBJECT_HPP__ 1

#include "object.hpp"
#include <string>
#include <boost/variant.hpp>

namespace Runtime
{
  class Object;
  class StdClass;
  
  class ValueObject : public Object
  {
    private:
      typedef Object super;
      boost::variant<int,float,std::string> value;

    public:
      int debug = 2;
      ValueObject(StdClass *klass, boost::variant<int,std::string> value);
      ValueObject(std::string value);
      ValueObject(int value);
      ValueObject(float value);
      int    isFalse();
      int    isNil();
      boost::variant<int,float,std::string> getValue();
  };
}

#endif