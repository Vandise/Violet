#include "headers/common.hpp"
#include <string>

SCENARIO("Parsing Constant Definitions", "[constantnode]")
{
  FrontEnd::Driver driver;
  const char *filename;
  WHEN("Given a constant definition")
  {
    filename = "test/constants/single.src";
    driver.parse(filename);

    THEN("A signle constant node is pushed to the stack")
    {
      REQUIRE(NodeStack::stack.size() == 1);
    }

    NodeStack::stack.clear();
  }
}

SCENARIO("Compiling Constant Definition", "[constantnode]")
{
  FrontEnd::Driver driver;
  Violet::Generator generator;
  const char *filename;

  filename = "test/constants/single.src";
  driver.parse(filename);

  WHEN("Compiling a constant node definition")
  {
    Context *context = new Context(Lang::Runtime::mainObject);
    NodeStack::stack[0]->compile(context, &generator); // call node

    THEN("The context is pushed onto the scopes table")
    {
      int index = generator.scopeIndex(context);
      REQUIRE(index == 0);
      REQUIRE(generator.scopes.size() == 1);
    }
    THEN("It emits PUSH_OBJECT onto the stack")
    {
      // print("hello world")
      REQUIRE(generator.instructions.size() == 3);
      std::vector<int> bytecode = {
        PUSH_OBJECT,  0, 0        // object name, scope
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