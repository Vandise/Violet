#include "headers/common.hpp"
#include <string>

SCENARIO("Parsing Class Definitions", "[constantnode]")
{
  FrontEnd::Driver driver;
  const char *filename;
  WHEN("Given a class definition")
  {
    filename = "test/class/single.src";
    driver.parse(filename);

    THEN("A single class node is pushed to the stack")
    {
      REQUIRE(NodeStack::stack.size() == 1);
    }

    NodeStack::stack.clear();
  }
}