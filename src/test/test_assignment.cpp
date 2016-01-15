#include "headers/common.hpp"
#include <string>

SCENARIO("Parsing Assignment Statements", "[localassignmentnode]")
{
  FrontEnd::Driver driver;
  const char *filename;
  WHEN("Given an assignment definition")
  {
    filename = "test/indentifiers/assignment.src";
    driver.parse(filename);

    THEN("An assignment node node is pushed to the nodestack")
    {
      REQUIRE(NodeStack::stack.size() == 1);
    }

    NodeStack::stack.clear();
  }
}

SCENARIO("Compiling Assignment Statement", "[localassignmentnode]")
{
  FrontEnd::Driver driver;
  Violet::Generator generator;
  const char *filename;

  filename = "test/indentifiers/assignment.src";
  driver.parse(filename);

  WHEN("Compiling an assignment node definition")
  {
    NodeStack::stack[0]->compile(new Context(Lang::Runtime::mainObject), &generator);

    THEN("The context is pushed onto the scopes table")
    {
      int index = generator.scopeIndex(new Context(Lang::Runtime::mainObject));
      REQUIRE(index == 0);
      REQUIRE(generator.scopes.size() == 1);
    }
    THEN("It emits PUSH_INTEGER and SET_LOCAL onto the stack")
    {
      // x = 5
      REQUIRE(generator.instructions.size() == 5);
      REQUIRE(generator.instructions[0] == PUSH_INTEGER); // instruction
      REQUIRE(generator.instructions[1] == 0);            // literal location
      REQUIRE(generator.instructions[2] == SET_LOCAL);    // instruction
      REQUIRE(generator.instructions[3] == 0);            // literals table variable name ( 0 = 5, 1 = x )
      REQUIRE(generator.instructions[4] == 0);            // index of context.locals
    }
    THEN("Context.locals contains the literal index of the defined variable")
    {
      REQUIRE(generator.scopes[0]->locals[0] == 1);
      std::string local_value = boost::get<std::string>(generator.literals[generator.scopes[0]->locals[0]]);
      REQUIRE(local_value.compare("x") == 0);
    }
  }
  NodeStack::stack.clear();
  generator.instructions.clear();
  generator.literals.clear();
  generator.locals.clear();
}