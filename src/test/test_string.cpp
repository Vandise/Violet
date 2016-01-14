#include "headers/common.hpp"
#include <string>

SCENARIO("Parsing Strings", "[literalnode]")
{
  FrontEnd::Driver driver;
  const char *filename;
  WHEN("Given a single string")
  {
    filename = "test/datatypes/string/single.src";
    driver.parse(filename);

    THEN("A string value-node is pushed to the nodestack")
    {
      REQUIRE(NodeStack::stack.size() == 1);
    }

    THEN("It contains the parsed value")
    {
      std::string value = boost::get<std::string>(((Nodes::LiteralNode*)NodeStack::stack[0])->value);
      REQUIRE(value.compare("string") == 0);
    }

    NodeStack::stack.clear();
  }
}

SCENARIO("Compiling Strings", "[literalnode]")
{
  FrontEnd::Driver driver;
  Violet::Generator generator;
  const char *filename;

  filename = "test/datatypes/string/single.src";
  driver.parse(filename);

  WHEN("A String is compiled")
  {
    NodeStack::stack[0]->compile(NULL, &generator);

    THEN("It is pushed onto the literals table")
    {
      int index = generator.literalIndex(std::string("string"));
      REQUIRE(index == 0);
    }

    THEN("It emits PUSH_STRING onto the stack with one operand")
    {
      REQUIRE(generator.instructions.size() == 2);
      REQUIRE(generator.instructions[0] == PUSH_STRING);
      REQUIRE(generator.instructions[1] == 0);
    }
  }
  NodeStack::stack.clear();
  generator.instructions.clear();
  generator.literals.clear();
  generator.locals.clear();
}