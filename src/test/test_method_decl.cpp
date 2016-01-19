#include "headers/common.hpp"
#include <string>

SCENARIO("Parsing Methods", "[methodnode]")
{
  FrontEnd::Driver driver;
  const char *filename;
  WHEN("Given a single method definition")
  {
    filename = "test/methods/single_declaration.src";
    driver.parse(filename);

    THEN("A method node is pushed to the nodestack")
    {
      REQUIRE(NodeStack::stack.size() == 1);
    }

    NodeStack::stack.clear();
  }
}

SCENARIO("Compiling Methods", "[methodnode]")
{
  FrontEnd::Driver driver;
  Violet::Generator generator;
  Context *context = new Context(Lang::Runtime::mainObject);
  const char *filename;

  filename = "test/methods/declaration.src";
  driver.parse(filename);

  WHEN("Compiling a declaration node definition")
  {
    for(int i = 0; i < NodeStack::stack.size(); i++)
    {
      NodeStack::stack[i]->compile(context, &generator);
    }
    THEN("It emits CALL onto the stack with one operand")
    {
      REQUIRE(generator.instructions.size() == 10);
      std::vector<int> bytecode = {
        PUSH_STRING, 0, // param 1
        PUSH_STRING, 1, // param 2
        PUSH_SELF,   0, // current scope
        PUSH_STRING, 2, // method name
        CALL,        2  // call with 2 arguments
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