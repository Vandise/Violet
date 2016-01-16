#include "headers/common.hpp"
#include <string>

SCENARIO("Parsing Get Local Statements", "[localnode]")
{
  FrontEnd::Driver driver;
  const char *filename;
  WHEN("Given an assignment and identifier definition")
  {
    filename = "test/indentifiers/getlocal.src";
    driver.parse(filename);

    THEN("An assignment node and localnode are pushed to the nodestack")
    {
      REQUIRE(NodeStack::stack.size() == 2);
    }

    NodeStack::stack.clear();
  }
}

SCENARIO("Compiling Local Statement", "[localnode]")
{
  FrontEnd::Driver driver;
  Violet::Generator generator;
  const char *filename;

  filename = "test/indentifiers/getlocal.src";
  driver.parse(filename);

  WHEN("Compiling a local node definition")
  {
    Context *context = new Context(Lang::Runtime::mainObject);
    NodeStack::stack[0]->compile(context, &generator); // assignment node
    NodeStack::stack[1]->compile(context, &generator); // local node

    THEN("The context is pushed onto the scopes table")
    {
      int index = generator.scopeIndex(context);
      REQUIRE(index == 0);
      REQUIRE(generator.scopes.size() == 1);
    }
    THEN("It emits GET_LOCAL onto the stack")
    {
      REQUIRE(generator.instructions.size() == 8);
      std::vector<int> bytecode = {
        PUSH_INTEGER, 0,
        SET_LOCAL,    0, 0,
        GET_LOCAL,    0, 0,
      };
      for(int i = 0; i < bytecode.size(); i++)
      {
        REQUIRE(generator.instructions[i] == bytecode[i]);
      }
    }
    WHEN("The local does not exist")
    {
      NodeStack::stack.clear();
      filename = "test/indentifiers/single.src";
      driver.parse(filename);
      THEN("It throws an out of range exception")
      {
        REQUIRE_NOTHROW(NodeStack::stack[0]->compile(context, &generator));
      }
    }
  }
  NodeStack::stack.clear();
  generator.instructions.clear();
  generator.literals.clear();
  generator.locals.clear();
}