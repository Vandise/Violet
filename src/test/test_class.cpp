#include "headers/common.hpp"
#include <string>

SCENARIO("Parsing Class Definitions", "[constantnode]")
{
  FrontEnd::Driver driver;
  const char *filename;
  WHEN("Given a class definition")
  {
    filename = "test/class/single.src";
    driver.parse(filename);

    THEN("A single class node is pushed to the stack")
    {
      REQUIRE(NodeStack::stack.size() == 1);
    }

    NodeStack::stack.clear();
  }
}

SCENARIO("Compiling Class Definition", "[constantnode]")
{
  FrontEnd::Driver driver;
  Violet::Generator generator;
  const char *filename;

  filename = "test/class/single.src";
  driver.parse(filename);
  Context *context = new Context(Lang::Runtime::mainObject);

  WHEN("Compiling a class definition node")
  {
    NodeStack::stack[0]->compile(context, &generator);

    THEN("The context is pushed onto the scopes table")
    {
      int index = generator.scopeIndex(context);
      REQUIRE(index == 1);
      REQUIRE(generator.scopes.size() == 2);
    }
    THEN("It emits PUSH_CONSTANT onto the stack")
    {
      REQUIRE(generator.instructions.size() == 3);
      std::vector<int> bytecode = {
        PUSH_CONSTANT, 0, 1
      };
      for(int i = 0; i < bytecode.size(); i++)
      {
        REQUIRE(generator.instructions[i] == bytecode[i]);
      }
    }
  }
  NodeStack::stack.clear();
  generator.instructions.clear();
  generator.literals.clear();
  generator.locals.clear();
}