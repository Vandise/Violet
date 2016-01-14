#include "headers/common.hpp"

SCENARIO("Parsing Floats", "[valueobject]")
{
  FrontEnd::Driver driver;
  const char *filename;
  WHEN("Given a single float")
  {
    filename = "test/datatypes/float/single.src";
    driver.parse(filename);

    THEN("A float value-node is pushed to the nodestack")
    {
      REQUIRE(NodeStack::stack.size() == 1);
    }

    THEN("It contains the parsed value")
    {
      float value = boost::get<float>(((Nodes::LiteralNode*)NodeStack::stack[0])->value);
      REQUIRE(value == 5.55555f);
    }

    NodeStack::stack.clear();
  }
}

SCENARIO("Compiling Floats", "[literalnode]")
{
  FrontEnd::Driver driver;
  Violet::Generator generator;
  const char *filename;

  filename = "test/datatypes/float/single.src";
  driver.parse(filename);

  WHEN("A Float is compiled")
  {
    NodeStack::stack[0]->compile(NULL, &generator);

    THEN("It is pushed onto the literals table")
    {
      int index = generator.literalIndex(5.55555f);
      REQUIRE(index == 0);
    }

    THEN("It emits PUSH_FLOAT onto the stack with one operand")
    {
      REQUIRE(generator.instructions.size() == 2);
      REQUIRE(generator.instructions[0] == PUSH_FLOAT);
      REQUIRE(generator.instructions[1] == 0);
    }
  }
  NodeStack::stack.clear();
  generator.instructions.clear();
  generator.literals.clear();
  generator.locals.clear();
}