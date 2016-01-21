%{

#include <algorithm>
#include <string>
#include <iostream>
#include "frontend/scanner.hpp"


typedef FrontEnd::Parser::token token;
bool term = false;

#define STOKEN( x ) ( new std::string( x ) )

#define STRIP_QUOTES( s ) ( s->erase(remove(s->begin(), s->end(), '\"' ), s->end()) )

#define yyterminate() return (term = !term)?Parser::token::PRGEND : YY_NULL

/* msvc2010 requires that we exclude this header file. */
#define YY_NO_UNISTD_H

%}

%option debug 
%option nodefault 
%option yyclass="FrontEnd::Scanner" 
%option noyywrap 
%option c++

digit ([0-9])
integer ({digit}+)
float_num ({digit}+\.{digit}+)

%%

[\ \t]+

"//".*      { /* DO NOTHING */ }

\n                  { 
                      return( token::NEWLINE );   
                    }

"self"              { return(token::SELF); }
"func"              { return(token::FUNC); }
"do"                { return(token::DO); }
"end"               { return(token::END); }

\"[^"]*\"           {
                      yylval->sval = STOKEN(yytext);
                      yylval->sval->erase(remove(yylval->sval->begin(), yylval->sval->end(), '\"' ), yylval->sval->end());
                      return(token::STRING);
                    }
([A-Z][a-zA-Z]*)+   {
                      yylval->sval = STOKEN(yytext);
                      return( token::CONSTANT );     
                    }
[_a-zA-Z\\?\\!]+    {
                      yylval->sval = STOKEN(yytext);
                      return( token::IDENTIFIER );
                    }       
{integer}           {
                      yylval->ival = (atoi(yytext));
                      return( token::INTEGER );
                    }
{float_num}         {
                      yylval->fval = (atof(yytext));
                      return( token::FLOAT );
                    }
"|"                 { return(token::PIPE); }
"->"                { return(token::LAMBDA); }
"="                 { return( token::ASSIGN ); }
"("                 { return( token::OPEN_PAREN );  }
")"                 { return( token::CLOSE_PAREN ); }  
","                 { return( token::COMMA ); }
"."                 { return( token::DOT ); }
.                   {  }

%%


