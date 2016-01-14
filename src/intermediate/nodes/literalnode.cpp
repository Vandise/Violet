#include "headers/literalnode.hpp"
#include "intermediate/headers/context.hpp"
#include "violet/headers/violetgenerator.hpp"

Nodes::LiteralNode::LiteralNode(boost::variant<int,float,std::string> value)
{
  this->value = value;
}

void
Nodes::LiteralNode::compile(Context *context, Violet::Generator *generator)
{
  if(this->value.type() == typeid(std::string))
  {
    generator->stringLiteral(this->value);
  }
  else if(this->value.type() == typeid(int))
  {
    generator->integerLiteral(this->value);
  }
  else
  {
    generator->floatLiteral(this->value);
  }
}