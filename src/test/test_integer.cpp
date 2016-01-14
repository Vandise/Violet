#include "headers/common.hpp"

SCENARIO("Parsing Integers", "[valueobject]")
{
  FrontEnd::Driver driver;
  const char *filename;
  WHEN("Given a single integer")
  {
    filename = "test/datatypes/integer/single.src";
    driver.parse(filename);

    THEN("An integer value-node is pushed to the nodestack")
    {
      REQUIRE(NodeStack::stack.size() == 1);
    }

    THEN("It contains the parsed value")
    {
      int value = boost::get<int>(((Nodes::LiteralNode*)NodeStack::stack[0])->value);
      REQUIRE(value == 10);
    }
    NodeStack::stack.clear();
  }
}

SCENARIO("Compiling Integers", "[literalnode]")
{
  FrontEnd::Driver driver;
  Violet::Generator generator;
  const char *filename;

  filename = "test/datatypes/integer/single.src";
  driver.parse(filename);

  WHEN("An Integer is compiled")
  {
    NodeStack::stack[0]->compile(NULL, &generator);

    THEN("It is pushed onto the literals table")
    {
      int index = generator.literalIndex(10);
      REQUIRE(index == 0);
    }

    THEN("It emits PUSH_STRING onto the stack with one operand")
    {
      REQUIRE(generator.instructions.size() == 2);
      REQUIRE(generator.instructions[0] == PUSH_INTEGER);
      REQUIRE(generator.instructions[1] == 0);
    }
  }
  NodeStack::stack.clear();
  generator.instructions.clear();
  generator.literals.clear();
  generator.locals.clear();
}