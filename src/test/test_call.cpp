#include "headers/common.hpp"
#include <string>

SCENARIO("Parsing Call Statements", "[callbide]")
{
  FrontEnd::Driver driver;
  const char *filename;
  WHEN("Given an assignment and identifier definition")
  {
    filename = "test/methods/single.src";
    driver.parse(filename);

    THEN("A signle call node is pushed to the stack")
    {
      REQUIRE(NodeStack::stack.size() == 1);
    }

    NodeStack::stack.clear();
  }
}

SCENARIO("Compiling Call Statement", "[callnode]")
{
  FrontEnd::Driver driver;
  Violet::Generator generator;
  const char *filename;

  filename = "test/methods/single.src";
  driver.parse(filename);

  WHEN("Compiling a local node definition")
  {
    Context *context = new Context(Lang::Runtime::mainObject);
    NodeStack::stack[0]->compile(context, &generator); // call node

    THEN("The context is pushed onto the scopes table")
    {
      int index = generator.scopeIndex(context);
      REQUIRE(index == 0);
      REQUIRE(generator.scopes.size() == 1);
    }
    THEN("It emits CALL onto the stack")
    {
      // print("hello world")
      REQUIRE(generator.instructions.size() == 8);
      std::vector<int> bytecode = {
        PUSH_STRING,  0,          // argument
        PUSH_SELF,    0,          // receiver
        PUSH_STRING,  1,          // method
        CALL,         1,          // CALL argument_count
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