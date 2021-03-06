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
      REQUIRE(index == 1);
      REQUIRE(generator.scopes.size() == 2);
    }
    THEN("It emits PUSH_LAMBDA onto the stack")
    {
      REQUIRE(generator.instructions.size() == 13);
      std::vector<int> bytecode = {
        PUSH_LAMBDA, 0, 1, 0, 1,   // scope, parameter size, parameter literal index, locals size
        SET_LOCAL,   0, 0,      // set parameter locals
        3,                      // body instruction count
        //---- body
        GET_LOCAL,   0, 0,  // literal index, scope
        //---- end body
        RETURN
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

  WHEN("Accessing a parent variable")
  {
    filename = "test/lambda/scope.src";
    driver.parse(filename);

    Context *context = new Context(Lang::Runtime::mainObject);
    for(int i = 0; i < NodeStack::stack.size(); i++)
    {
      NodeStack::stack[i]->compile(context, &generator);
    }

    THEN("The parent variable can be accessed appropriately")
    {
      REQUIRE(generator.instructions.size() == 24);
      std::vector<int> bytecode = {
        PUSH_INTEGER, 0,            // push the integer
        SET_LOCAL,    0, 0,         // set parent local
        PUSH_LAMBDA,  1, 1, 0, 1,   // scope, parameter size, parameter literal index, locals size
        SET_LOCAL,    0, 1,         // set parameter locals
        6,                          // body instruction count
        //---- body
        GET_LOCAL,   0, 1,          // literal index, scope
        GET_LOCAL,   0, 0,          // literal index, parent scope
        //---- end body
        RETURN,                     // return lambda
        SET_LOCAL,   1, 0           // assign lambda object to variable
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
