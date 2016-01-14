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

