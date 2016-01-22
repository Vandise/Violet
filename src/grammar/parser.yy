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
   #include "intermediate/nodes/headers/localassignnode.hpp"
   #include "intermediate/nodes/headers/localnode.hpp"
   #include "intermediate/nodes/headers/methoddefinitionnode.hpp"
   #include "intermediate/nodes/headers/constantnode.hpp"
   #include "intermediate/nodes/headers/lambdanode.hpp"
   #include "intermediate/nodes/headers/classdefinitionnode.hpp"

#undef yylex
#define yylex scanner.yylex
   
}

%token   <ival>   INTEGER
%token   <fval>   FLOAT
%token   <sval>   STRING
%token            SELF

%token   <sval>   CONSTANT
%token   <sval>   IDENTIFIER

%token            ASSIGN
%token            OPEN_PAREN
%token            CLOSE_PAREN
%token            COMMA
%token            FUNC
%token            DO
%token            END
%token            DOT
%token            PIPE
%token            LAMBDA
%token            CLASS

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


%type <abs_node>     Expression Literal Call Class SetLocal GetLocal Function GetConstant Lambda
%type <driver>       Expressions
%type <nodes>        BodyExpressions
%type <arguments>    Arguments
%type <parameters>   Parameters

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


BodyExpressions: 
    Expression                            {
                                            std::vector<Nodes::AbstractNode *> nodes;
                                            nodes.push_back($1);
                                            Nodes::Nodes *nodelist = new Nodes::Nodes(nodes);
                                            $$ = nodelist;
                                          }
  | BodyExpressions Terminator Expression {
                                            $1->add($3);
                                            $$ = $1;
                                          }
  |                                       { /* do nothing */ }
  | BodyExpressions Terminator            {
                                            $$ = $1;
                                          }
  ;

Expression:
    Literal
  | Call
  | GetConstant
  | SetLocal
  | GetLocal
  | Function
  | Lambda
  | Class
  | OPEN_PAREN Expression CLOSE_PAREN     { $$ = $2; }
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

Call:
    IDENTIFIER OPEN_PAREN Arguments CLOSE_PAREN                   { $$ = new Nodes::CallNode(*$1, NULL, *$3); }
  | Expression DOT IDENTIFIER OPEN_PAREN Arguments CLOSE_PAREN    { $$ = new Nodes::CallNode(*$3, $1, *$5);   }
  ;

Function:
  FUNC IDENTIFIER OPEN_PAREN Parameters CLOSE_PAREN Terminator
    BodyExpressions
  END                             {
                                    $$ = new Nodes::MethodDefinitionNode(*$2, *$4, $7);
                                  }
  ;


Lambda:
    LAMBDA DO PIPE Parameters PIPE Terminator
      BodyExpressions
    END                           {
                                    $$ = new Nodes::LambdaNode(*$4,$7);
                                  }
  ;

Arguments:
    Expression                  {
                                  std::vector<Nodes::AbstractNode*> *arguments = new std::vector<Nodes::AbstractNode*>();
                                  arguments->push_back($1);
                                  $$ = arguments;
                                }
  | Arguments COMMA Expression  {
                                  $1->push_back($3);
                                  $$ = $1;
                                }
  |                             {
                                  std::vector<Nodes::AbstractNode*> *arguments = new std::vector<Nodes::AbstractNode*>();
                                  $$ = arguments;
                                }
  ;

Parameters:
    IDENTIFIER                    {
                                    std::vector<std::string> *parameters = new std::vector<std::string>();
                                    parameters->push_back(*$1);
                                    $$ = parameters;
                                  }
  |  Parameters COMMA IDENTIFIER  { $1->push_back(*$3); $$ = $1; }
  |                               { 
                                    std::vector<std::string> *parameters = new std::vector<std::string>();
                                    $$ = parameters;
                                  }
  ;

Class:
    CLASS CONSTANT Terminator
      BodyExpressions
    END                           {
                                    $$ = new Nodes::ClassDefinitionNode(*$2, std::string(""), $4);
                                  }
  ;

SetLocal:
    IDENTIFIER ASSIGN Expression     { $$ = new Nodes::LocalAssignNode(*$1, $3); }
  ;

GetLocal:
    IDENTIFIER    { $$ = new Nodes::LocalNode(*$1); }
  ;

GetConstant:
    CONSTANT                      { $$ = new Nodes::ConstantNode(*$1); }
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