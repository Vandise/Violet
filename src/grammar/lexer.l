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

"class"             { return(token::CLASS); }
"self"              { return(token::SELF); }
"func"              { return(token::FUNC); }
"do"                { return(token::DO); }
"if"                { return(token::IF); }
"end"               { return(token::END); }
"operator"          { return(token::OPERATOR); }
"ret"               { return(token::RETURN); }

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
"("                 { return( token::OPEN_PAREN );  }
")"                 { return( token::CLOSE_PAREN ); }  
","                 { return( token::COMMA ); }
"."                 { return( token::DOT ); }
":"                 { return( token::COLON ); }

"&&"         {
                yylval->sval = STOKEN(yytext); 
                return( token::AND ); 
             }
"||"         {
                yylval->sval = STOKEN(yytext); 
                return( token::OR ); 
             }
"=="         {
                yylval->sval = STOKEN(yytext); 
                return( token::EQ ); 
             }  
"<="         {
              yylval->sval = STOKEN(yytext);
              return( token::LE );
            }
">="        {
              yylval->sval = STOKEN(yytext);
              return( token::GE );
            }          
"="         { return( token::ASSIGN ); }
"<"         {
              yylval->sval = STOKEN(yytext);
              return( token::LT );
            }
">"         {
              yylval->sval = STOKEN(yytext);
              return( token::GT );
            }
"+"         {
              yylval->sval = STOKEN(yytext);
              return( token::PLUS );
            }

"-"         {
              yylval->sval = STOKEN(yytext);
              return( token::MINUS );
            }

"*"         {
              yylval->sval = STOKEN(yytext);
              return( token::MULT );
            }

"/"         {
              yylval->sval = STOKEN(yytext);
              return( token::DIV );
            }

.                   {  }

%%


