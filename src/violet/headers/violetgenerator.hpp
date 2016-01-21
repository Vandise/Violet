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

      int localIndex(int literal_index, Context *context);
      int literalIndex(boost::variant<int,float,std::string> literal);
      int getLocalIndex(int value, std::vector< int > *table);
      int scopeIndex(Context *context);
      int getIndex(boost::variant<int,float,std::string> search, std::vector< boost::variant<int,float,std::string> > *table);
      int getScope(Context *context);
      void integerLiteral(boost::variant<int,float,std::string> value);
      void stringLiteral(boost::variant<int,float,std::string> value);
      void floatLiteral(boost::variant<int,float,std::string> value);
      void selfLiteral(Context *self);
      void getLocal(std::string name, Context *context);
      void setLocal(std::string name, Context *context);
      void callMethod(int argc);
      void pushObject(std::string name, Context *context);
      void emit(int opcode, std::vector<int> operands);
      void emitByte(int operand);
      void assemble();
  };

}
#endif
