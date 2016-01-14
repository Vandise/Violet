#include "headers/selfnode.hpp"
#include "intermediate/headers/context.hpp"
#include "violet/headers/violetgenerator.hpp"

void
Nodes::SelfNode::compile(Context *context, Violet::Generator *generator)
{
  generator->selfLiteral(context);
}