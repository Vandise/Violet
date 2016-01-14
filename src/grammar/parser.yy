%skeleton "lalr1.cc"
%require  "3.0"
%defines 
%define api.namespace {FrontEnd}
%define parser_class_name {Parser}
%define parse.trace

%code requires{
#include <vector>
  namespace FrontEnd {
    class Driver;
    class Scanner;
  }
  
  namespace Nodes
  {
   class Nodes;
   class AbstractNode;
   class LiteralNode;
   class CallNode;
   class MethodDefinitionNode;
  }
  
  namespace Runtime
  {
   class ValueObject;
  }
  
  namespace Lang
  {
   class Runtime;
  }
  
  class NodeStack;
}

%parse-param { Scanner  &scanner  }
%parse-param { Driver  &driver  }

%code{
   #include <iostream>
   #include <cstdlib>
   #include <fstream>
   #include <map>
   #include <vector>

   /* include for all driver functions */
   #include "intermediate/headers/driver.hpp"
   #include "runtime/headers/runtime.hpp"
   #include "intermediate/nodes/headers/abstractnode.hpp"
   #include "intermediate/nodes/headers/nodes.hpp"
   #include "intermediate/nodes/headers/callnode.hpp"
   #include "intermediate/nodes/headers/literalnode.hpp"
   #include "intermediate/nodes/headers/selfnode.hpp"

#undef yylex
#define yylex scanner.yylex
   
}

%token   <ival>   INTEGER
%token   <fval>   FLOAT
%token   <sval>   STRING
%token            SELF

%token            NEWLINE 
%token            PRGEND 0     "end of file"


/* destructor rule for <sval> objects */
%destructor { if ($$)  { delete ($$); ($$) = nullptr; } } <sval>

%left  "."
%right "!"
%left  "*" "/"
%left  "+" "-"
%left  ">" ">=" "<" "<="
%left  "==" "!="
%left  "&&"
%left  "||"
%right "="
%left  ","

/* token types */
%union {
   std::string                        *sval;
   int                                 ival;
   float                               fval;
   Nodes::LiteralNode                 *lit_node;
   Nodes::AbstractNode                *abs_node;
   std::vector<Nodes::AbstractNode *> *expressions;
   FrontEnd::Driver                   *driver;
   Nodes::Nodes                       *nodes;
   std::vector<std::string>           *parameters;
   std::vector<Nodes::AbstractNode*>  *arguments;
}


%type <abs_node>     Expression Literal
%type <driver>       Expressions

%%

Expressions:
    Expression                              {
                                              std::vector<Nodes::AbstractNode *> nodes;
                                              nodes.push_back($1);
                                              driver.push_stack(nodes);
                                              $$ = &driver;
                                            }
  | Expressions Terminator Expression       {
                                              $1->push_node($3);
                                              $$ = $1;
                                            }
  |                                         {
    
                                            }
  | Expressions Terminator                  {
                                              $$ = $1;
                                            }
  ;

Expression:
    Literal
  ;

Literal:
    INTEGER                 {
                              $$ = new Nodes::LiteralNode($1);
                            }
  | FLOAT                   {
                              $$ = new Nodes::LiteralNode($1);
                            }
  | STRING                  {
                              $$ = new Nodes::LiteralNode(*$1);
                            }
  | SELF                    {
                              $$ = new Nodes::SelfNode();
                            }
  ;

Terminator:
  NEWLINE
  ;
%%


void 
FrontEnd::Parser::error( const std::string &err_message )
{
   std::cerr << "Error: " << err_message << "\n"; 
}