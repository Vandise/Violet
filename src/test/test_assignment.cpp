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
  Context *context = new Context(Lang::Runtime::mainObject);

  WHEN("Compiling an assignment node definition")
  {
    NodeStack::stack[0]->compile(context, &generator);

    THEN("The context is pushed onto the scopes table")
    {
      int index = generator.scopeIndex(context);
      REQUIRE(index == 0);
      REQUIRE(generator.scopes.size() == 1);
    }
    THEN("It emits PUSH_INTEGER and SET_LOCAL onto the stack")
    {
      REQUIRE(generator.instructions.size() == 5);
      std::vector<int> bytecode = {
        PUSH_INTEGER, 0,
        SET_LOCAL,    0, 0
      };
      for(int i = 0; i < bytecode.size(); i++)
      {
        REQUIRE(generator.instructions[i] == bytecode[i]);
      }
    }
    THEN("Context.local_bytes contains the literal index of the defined variable")
    {
      REQUIRE(generator.scopes[0]->local_bytes[0] == 1);
      std::string local_value = boost::get<std::string>(generator.literals[generator.scopes[0]->local_bytes[0]]);
      REQUIRE(local_value.compare("x") == 0);
    }
  }
  NodeStack::stack.clear();
  generator.instructions.clear();
  generator.literals.clear();
  generator.locals.clear();
}