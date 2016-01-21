#ifndef __COMMONTEST_HPP__
#define __COMMONTEST_HPP__ 1

#include <catch.h>
#include <iostream>
#include <stdexcept>
#include <boost/variant.hpp>
#include <boost/variant/get.hpp>
#include "intermediate/headers/bytecode.hpp"
#include "intermediate/nodes/headers/abstractnode.hpp"
#include "intermediate/nodes/headers/literalnode.hpp"
#include "intermediate/nodes/headers/selfnode.hpp"
#include "intermediate/nodes/headers/localassignnode.hpp"
#include "intermediate/nodes/headers/localnode.hpp"
#include "intermediate/nodes/headers/callnode.hpp"
#include "intermediate/nodes/headers/methoddefinitionnode.hpp"
#include "intermediate/nodes/headers/constantnode.hpp"
#include "intermediate/nodes/headers/lambdanode.hpp"
#include "intermediate/headers/driver.hpp"
#include "intermediate/headers/nodestack.hpp"
#include "runtime/headers/runtime.hpp"
#include "runtime/headers/stdclass.hpp"
#include "intermediate/headers/context.hpp"
#include "runtime/headers/valueobject.hpp"
#include "violet/headers/violetgenerator.hpp"

#endif