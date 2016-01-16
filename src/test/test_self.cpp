#include "headers/common.hpp"
#include <string>

SCENARIO("Parsing Self", "[selfnode]")
{
  FrontEnd::Driver driver;
  const char *filename;
  WHEN("Given a single self definition")
  {
    filename = "test/datatypes/self/single.src";
    driver.parse(filename);

    THEN("A self node is pushed to the nodestack")
    {
      REQUIRE(NodeStack::stack.size() == 1);
    }

    NodeStack::stack.clear();
  }
}

SCENARIO("Compiling Self", "[selfnode]")
{
  FrontEnd::Driver driver;
  Violet::Generator generator;
  Context *context = new Context(Lang::Runtime::mainObject);
  const char *filename;

  filename = "test/datatypes/self/single.src";
  driver.parse(filename);

  WHEN("Compiling a self node definition")
  {
    NodeStack::stack[0]->compile(context, &generator);

    THEN("It is pushed onto the scopes table")
    {
      int index = generator.scopeIndex(context);
      REQUIRE(index == 0);
      REQUIRE(generator.scopes.size() == 1);
    }
    THEN("It emits PUSH_SELF onto the stack with one operand")
    {
      REQUIRE(generator.instructions.size() == 2);
      std::vector<int> bytecode = {
        PUSH_SELF, 0
      };
      for(int i = 0; i < bytecode.size(); i++)
      {
        REQUIRE(generator.instructions[i] == bytecode[i]);
      }
    }
    THEN("It defaults to [main] Object scope")
    {
      std::string objName = (generator.scopes[generator.instructions[1]])->getCurrentClass()->getName();
      REQUIRE(objName.compare("Object") == 0);
    }
  }
  NodeStack::stack.clear();
  generator.instructions.clear();
  generator.literals.clear();
  generator.locals.clear();
}