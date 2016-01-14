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

