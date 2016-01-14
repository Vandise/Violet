#define CATCH_CONFIG_RUNNER
#include <iostream>
#include "catch.h"
#include "runtime/headers/bootstrapper.hpp"

int main( int argc, char* const argv[] )
{
  Bootstrapper bootstrapper;
  bootstrapper.run();
  int result = Catch::Session().run( argc, argv );
  return result;
}