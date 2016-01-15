#include "headers/common.hpp"

/*
SCENARIO("Adding elements to locals", "[violetgenerator]")
{
  Violet::Generator generator;
  WHEN("Pushing a unique value")
  {
    boost::variant<int,float,std::string> value = 10;
    THEN("The value is pushed to the stack")
    {
      int index = generator.localIndex(value);
      REQUIRE(index == 0);
    }
  }

  WHEN("The value already exists")
  {
    boost::variant<int,float,std::string> value = 10;
    THEN("Then previous index is returned")
    {
      generator.localIndex(value);
      int index = generator.localIndex(value);
      REQUIRE(index == 0);
    }
  }
}
*/

SCENARIO("Adding elements to literals", "[violetgenerator]")
{
  Violet::Generator generator;
  WHEN("Pushing a unique value")
  {
    boost::variant<int,float,std::string> value = 10;
    THEN("The value is pushed to the stack")
    {
      int index = generator.literalIndex(value);
      REQUIRE(index == 0);
    }
  }

  WHEN("The value already exists")
  {
    boost::variant<int,float,std::string> value = 10;
    THEN("Then previous index is returned")
    {
      generator.literalIndex(value);
      int index = generator.literalIndex(value);
      REQUIRE(index == 0);
    }
  }
}

SCENARIO("Comparing different datatypes","[violetgenerator]")
{
  Violet::Generator generator;
  WHEN("Tables contain different datatypes")
  {
    boost::variant<int,float,std::string> val_one = 10;
    boost::variant<int,float,std::string> val_two = std::string("String");
    boost::variant<int,float,std::string> val_three = 10.55f;
    THEN("The appropriate index is retrieved")
    {
      generator.literalIndex(val_one);
      generator.literalIndex(val_two);
      generator.literalIndex(val_three);
      REQUIRE(generator.literalIndex(val_one) == 0);
      REQUIRE(generator.literalIndex(val_two) == 1);
      REQUIRE(generator.literalIndex(val_three) == 2);
    }
  }
}