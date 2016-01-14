#include <cctype>
#include <fstream>
#include <cassert>

#include "headers/driver.hpp"
#include "headers/nodestack.hpp"
#include "headers/context.hpp"
#include "nodes/headers/nodes.hpp"
#include "nodes/headers/literalnode.hpp"
#include "nodes/headers/callnode.hpp"

FrontEnd::Driver::~Driver()
{
   delete(scanner);
   scanner = nullptr;
   delete(parser);
   parser = nullptr;
}

void
FrontEnd::Driver::push_stack(std::vector<Nodes::AbstractNode*> stack)
{
  for(int i = 0; i < stack.size(); i++)
  {
    NodeStack::stack.push_back(stack[i]);
  }
}

void
FrontEnd::Driver::push_node(Nodes::AbstractNode *node)
{
  NodeStack::stack.push_back(node);
}

void
FrontEnd::Driver::parse( const char * const filename )
{
   assert( filename != nullptr );
   std::ifstream in_file( filename );
   if( ! in_file.good() ) exit( EXIT_FAILURE );

   delete(scanner);
   try
   {
      scanner = new FrontEnd::Scanner( &in_file );
   }
   catch( std::bad_alloc &ba )
   {
      std::cerr << "Failed to allocate scanner: (" <<
         ba.what() << "), exiting!!\n";
      exit( EXIT_FAILURE );
   }
   delete(parser);
   try
   {
      parser = new FrontEnd::Parser( (*scanner) /* scanner */, 
                                  (*this) /* driver */ );
   }
   catch( std::bad_alloc &ba )
   {
      std::cerr << "Failed to allocate parser: (" << 
         ba.what() << "), exiting!!\n";
      exit( EXIT_FAILURE );
   }

   parser->parse();
}

Runtime::Object*
FrontEnd::Driver::execute(Context *context)
{
  //Nodes::Nodes *node = new Nodes::Nodes(NodeStack::stack);
  //return node->eval(context);
  return NULL;
}