#ifndef __VIOLETGENERATOR_HPP__
#define __VIOLETGENERATOR_HPP__ 1

#include <string>
#include <cstdint>
#include <vector>
#include <boost/variant.hpp>

class Context;

namespace Violet
{

  class Generator
  {
    public:
      std::vector< boost::variant<int,float,std::string> > literals;
      std::vector< boost::variant<int,float,std::string> > locals;
      std::vector<int> instructions;
      std::vector<Context*> scopes;

      int localIndex(boost::variant<int,float,std::string> local);
      int literalIndex(boost::variant<int,float,std::string> literal);
      int scopeIndex(Context *context);
      int getIndex(boost::variant<int,float,std::string> search, std::vector< boost::variant<int,float,std::string> > *table);
      int getScope(Context *context);
      void integerLiteral(boost::variant<int,float,std::string> value);
      void stringLiteral(boost::variant<int,float,std::string> value);
      void floatLiteral(boost::variant<int,float,std::string> value);
      void selfLiteral(Context *self);
      void emit(int opcode, std::vector<int> operands);
  };

}
#endif
