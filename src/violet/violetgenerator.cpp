#include "intermediate/headers/context.hpp"
#include "headers/violetgenerator.hpp"
#include "intermediate/headers/bytecode.hpp"
#include "runtime/headers/stdclass.hpp"

/* ---------------- LOCAL INDEX MANAGEMENT ---------------- */

int
Violet::Generator::localIndex(int literal_index, Context *context)
{
  int index = this->getLocalIndex(literal_index, &context->locals);
  if(index >= 0)
  {
    return index;
  }
  context->locals.push_back(literal_index);
  return context->locals.size() - 1;
}

int
Violet::Generator::getLocalIndex(int value, std::vector< int > *table)
{
  auto pred = [value](const int & search)
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

/* ---------------- LITERAL INDEX MANAGEMENT ---------------- */

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

/* ---------------- SCOPE MANAGEMENT ---------------- */

int
Violet::Generator::scopeIndex(Context *context)
{
  int index = this->getScope(context);
  if(index >= 0)
  {
    return index;
  }
  this->scopes.push_back(context);
  return this->scopes.size() - 1;
}

int
Violet::Generator::getScope(Context *context)
{
  auto pred = [context](Context* search)
  {
    int value = search->getCurrentClass()->getName().compare(context->getCurrentClass()->getName());
    return value == 0;
  };

  auto index =  std::find_if(this->scopes.begin(), this->scopes.end(), pred);
  if(index != this->scopes.end())
  {
    return index - this->scopes.begin();
  }
  return -1;
}

/* ---------------- INSTRUCTION GENERATION ---------------- */

/*
  integer literal
    PUSH_INTEGER [ integer literal index ]
*/
void
Violet::Generator::integerLiteral(boost::variant<int,float,std::string> value)
{
  std::vector<int> operands;
  operands.push_back(literalIndex(value));
  emit(PUSH_INTEGER, operands);
}

/*
  string literal
    PUSH_STRING [ string literal index ]
*/
void
Violet::Generator::stringLiteral(boost::variant<int,float,std::string> value)
{
  std::vector<int> operands;
  operands.push_back(literalIndex(value));
  emit(PUSH_STRING, operands);
}

/*
  float literal
    PUSH_FLOAT [ float literal index ]
*/
void
Violet::Generator::floatLiteral(boost::variant<int,float,std::string> value)
{
  std::vector<int> operands;
  operands.push_back(literalIndex(value));
  emit(PUSH_FLOAT, operands);
}

/*
  self literal
    PUSH_SELF [scope index]
*/
void
Violet::Generator::selfLiteral(Context *self)
{
  std::vector<int> operands;
  operands.push_back(scopeIndex(self));
  emit(PUSH_SELF, operands);
}

/*
  get local variable
    GET_LOCAL [literal index] [scope index]
*/
void
Violet::Generator::getLocal(std::string name, Context *context)
{
  std::vector<int> operands;
  operands.push_back(literalIndex(name));
  operands.push_back(scopeIndex(context));
  emit(GET_LOCAL, operands);
}

/*
  get local variable
    SET_LOCAL [context local index] [scope index]

  x = 5
  push_integer 5
  literal[0] = 5
  literal[1] = x
  Context
    - locals [0, literal_index 1]
*/
void
Violet::Generator::setLocal(std::string name, Context *context)
{
  std::vector<int> operands;
  operands.push_back(
    localIndex(literalIndex(name), this->scopes[scopeIndex(context)])
  );
  operands.push_back(scopeIndex(context));
  emit(SET_LOCAL, operands);
}

/* ---------------- EMIT INSTRUCTION ---------------- */

/*
  emit onto the instructions stack
    OPCODE [operand1,operand2...]
*/
void
Violet::Generator::emit(int opcode, std::vector<int> operands)
{
  this->instructions.push_back(opcode);
  for(int i = 0; i < operands.size(); i++)
  {
    this->instructions.push_back(operands[i]);
  }
}