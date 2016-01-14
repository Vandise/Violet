#include "headers/violetgenerator.hpp"
#include "intermediate/headers/bytecode.hpp"

int
Violet::Generator::localIndex(boost::variant<int,float,std::string> local)
{
  int index = this->getIndex(local,&this->locals);
  if(index >= 0)
  {
    return index;
  }
  this->locals.push_back(local);
  return this->locals.size() - 1;
}

int
Violet::Generator::literalIndex(boost::variant<int,float,std::string> literal)
{
  int index = this->getIndex(literal,&this->literals);
  if(index >= 0)
  {
    return index;
  }
  this->literals.push_back(literal);
  return this->literals.size() - 1;
}

int
Violet::Generator::getIndex(boost::variant<int,float,std::string> value, std::vector< boost::variant<int,float,std::string> > *table)
{
  auto pred = [value](const boost::variant<int,float,std::string> & search)
  {
    return search == value;
  };

  auto index =  std::find_if(table->begin(), table->end(), pred);
  if(index != table->end())
  {
    return index - table->begin();
  }
  return -1;
}

void
Violet::Generator::integerLiteral(boost::variant<int,float,std::string> value)
{
  std::vector<int> operands;
  operands.push_back(literalIndex(value));
  emit(PUSH_INTEGER, operands);
}

void
Violet::Generator::stringLiteral(boost::variant<int,float,std::string> value)
{
  std::vector<int> operands;
  operands.push_back(literalIndex(value));
  emit(PUSH_STRING, operands);
}

void
Violet::Generator::floatLiteral(boost::variant<int,float,std::string> value)
{
  std::vector<int> operands;
  operands.push_back(literalIndex(value));
  emit(PUSH_FLOAT, operands);
}

void
Violet::Generator::emit(int opcode, std::vector<int> operands)
{
  this->instructions.push_back(opcode);
  for(int i = 0; i < operands.size(); i++)
  {
    this->instructions.push_back(operands[i]);
  }
}