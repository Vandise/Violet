#include "headers/common.hpp"
#include <string>

SCENARIO("Parsing Lambda Definitions", "[lambdanode]")
{
  FrontEnd::Driver driver;
  const char *filename;
  WHEN("Given a lambda definition")
  {
    filename = "test/lambda/single.src";
    driver.parse(filename);

    THEN("A single lambda node is pushed to the stack")
    {
      REQUIRE(NodeStack::stack.size() == 1);
    }

    NodeStack::stack.clear();
  }
}


SCENARIO("Compiling Lambda Definition", "[lambdanode]")
{
  FrontEnd::Driver driver;
  Violet::Generator generator;
  const char *filename;

  filename = "test/lambda/single.src";
  driver.parse(filename);

  WHEN("Compiling a Lambda node definition")
  {
    Context *context = new Context(Lang::Runtime::mainObject);
    NodeStack::stack[0]->compile(context, &generator); // call node

    THEN("The context is pushed onto the scopes table")
    {
      int index = generator.scopeIndex(context);
      REQUIRE(index == 0);
      REQUIRE(generator.scopes.size() == 1);
    }
    THEN("It emits PUSH_LAMBDA onto the stack")
    {
      REQUIRE(generator.instructions.size() == 8);
      std::vector<int> bytecode = {
        PUSH_LAMBDA, 1, 0,   // parameter size, parameter literal index
        3,                   // body instruction count
        //---- body
        GET_LOCAL,   0, 0,  // literal index, scope
        //---- end body
        0                   // scope index
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
