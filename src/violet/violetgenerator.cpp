#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <boost/algorithm/string/join.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include "intermediate/nodes/headers/abstractnode.hpp"
#include "intermediate/headers/context.hpp"
#include "headers/violetgenerator.hpp"
#include "intermediate/headers/bytecode.hpp"
#include "runtime/headers/stdclass.hpp"
#include "runtime/headers/lambda.hpp"

/* ---------------- LOCAL INDEX MANAGEMENT ---------------- */

int
Violet::Generator::localIndex(int literal_index, Context *context)
{
  int index = this->getLocalIndex(literal_index, &context->local_bytes);
  if(index >= 0)
  {
    return index;
  }
  context->local_bytes.push_back(literal_index);
  return context->local_bytes.size() - 1;
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
    //
    // todo: compare pointers instead of class name
    //      this will break a lot of tests!
    //
    //int value = search->getCurrentClass()->getName().compare(context->getCurrentClass()->getName());
    return search == context;
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
  int local_index = getLocalIndex(literalIndex(name),&((this->scopes[scopeIndex(context)])->local_bytes));
  // does the local variable exist?
  if(local_index < 0)
    throw std::out_of_range("Call to undefined variable '"+name+"'.");

  operands.push_back(local_index);
  operands.push_back(scopeIndex(context));
  emit(GET_LOCAL, operands);
}

/*
  get local variable
    SET_LOCAL [context local index] [scope index]

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


/*
  Calls a method
    CALL [ number of arguments ]
    stack: [arg1...arg2, receiver, method]

*/
void
Violet::Generator::callMethod(int argc)
{
  std::vector<int> operands;
  operands.push_back(argc);
  emit(CALL, operands);
}

/*
  Pushes a user-defined or runtime object onto the stack
    PUSH_CONSTANT [ object ]
*/
void
Violet::Generator::pushConstant(std::string name, Context *context)
{
  std::vector<int> operands;
  operands.push_back(
    localIndex(literalIndex(name), this->scopes[scopeIndex(context)])
  );
  operands.push_back(scopeIndex(context));
  emit(PUSH_CONSTANT, operands);
}

/*
  Pushes lambda instructions onto the stack
    PUSH_LAMBDA [ parameter_size, params_literal_index..., instruction size, scope index ]
*/
void
Violet::Generator::pushLambda(std::vector<std::string> parameters, Nodes::AbstractNode *body, Context *parent)
{
  std::vector<int>  operands;
  Violet::Generator generator;
  generator.literals = this->literals;

  Context *context = parent->makeChildContext();

  operands.push_back(scopeIndex(context));

  operands.push_back(parameters.size());
  for(int i = 0; i < parameters.size(); i++)
  {
    operands.push_back(localIndex(literalIndex(parameters[i]), this->scopes[scopeIndex(context)]));
  }

  operands.push_back(parameters.size());
  for(int i = 0; i < parameters.size(); i++)
  {
    operands.push_back(SET_LOCAL);
    operands.push_back(localIndex(literalIndex(parameters[i]), this->scopes[scopeIndex(context)]));
    operands.push_back(scopeIndex(context));
  }

  generator.literals = this->literals;
  generator.scopes   = this->scopes;

  body->compile(context, &generator);

  operands.push_back(generator.instructions.size());
  for(int i = 0; i < generator.instructions.size(); i++)
  {
    operands.push_back(generator.instructions[i]);
  }
  operands.push_back(RETURN);
  emit(PUSH_LAMBDA, operands);

  this->literals = generator.literals;
  this->scopes   = generator.scopes;

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

/*
  pushes a byte onto the instruction stack, usually a literal from a node
*/
void
Violet::Generator::emitByte(int operand)
{
  this->instructions.push_back(operand);
}

void
Violet::Generator::assemble()
{
  emitByte(RETURN);
  for(int i = 0; i < this->scopes.size(); i++)
  {
    (this->scopes[i])->locals.reserve(
      (this->scopes[i])->local_bytes.size()
    );
  }
}