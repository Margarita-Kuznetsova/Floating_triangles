%{

//------------------------------------------------------------------------------
//
// scanner.l -- lexical rules for ParaCL v2
//
//------------------------------------------------------------------------------

#include "/home/margo/FloatingTriangles/Love/parser.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ScanError(char const *, char const *, int lineno);

%}

id          [a-zA-Z][a-zA-Z_0-9]*
data        ["][^"]*["]
ws          [ \t]+
int         [0-9]+
com         [#][^\n]*
%option yylineno

%%
{com}       {}
"\r"        {}
{ws}        {  BeginToken(yytext, &yyinlinePos); }
"Func"       {
               BeginToken(yytext, &yyinlinePos);
               return DEF;
            }   
"when"        {
               BeginToken(yytext, &yyinlinePos);
               return IF;
            }   
"unless"    {
               BeginToken(yytext, &yyinlinePos);
               return WHILE;
            }
"output"     {
               BeginToken(yytext, &yyinlinePos);
               return OUTPUT;
            }
"ret"       {
               BeginToken(yytext, &yyinlinePos);
               return RET;
            }
"plus"         {  BeginToken(yytext, &yyinlinePos); return PLUS;  }
"minus"         {  BeginToken(yytext, &yyinlinePos); return MINUS;  }
"x"         {  BeginToken(yytext, &yyinlinePos); return MUL;  }
"div"         {  BeginToken(yytext, &yyinlinePos); return DIV;  }
"("         {  BeginToken(yytext, &yyinlinePos); return LPAR;  }
")"         {  BeginToken(yytext, &yyinlinePos); return RPAR;  }
"["         {  BeginToken(yytext, &yyinlinePos); return LBR;  }
"]"         {  BeginToken(yytext, &yyinlinePos); return RBR;  }
"<"         {  BeginToken(yytext, &yyinlinePos); return LCB;  }
">"         {  BeginToken(yytext, &yyinlinePos); return RCB;  }
"|"         {  BeginToken(yytext, &yyinlinePos); return UP;  }
","         {  BeginToken(yytext, &yyinlinePos); return COMMA;  }
"\n"         {  BeginToken(yytext, &yyinlinePos); return NLINE;  }
"->"        {  BeginToken(yytext, &yyinlinePos); return ASG;  }
"@"         {  BeginToken(yytext, &yyinlinePos); return DOG;  }
"equal"        {  BeginToken(yytext, &yyinlinePos);  
               yylval.set(Ops::Equal);
               return RELOP;
            }
"not"        {
               BeginToken(yytext, &yyinlinePos);
               yylval.set(Ops::NotEqual);
               return RELOP;
            }
"less"         {
               BeginToken(yytext, &yyinlinePos);
               yylval.set(Ops::Less);
               return RELOP;
            }
"more"         {
               BeginToken(yytext, &yyinlinePos);
               yylval.set(Ops::Greater);
               return RELOP;
            }
"less_equal"        {
               BeginToken(yytext, &yyinlinePos);
               yylval.set(Ops::LessEq);
               return RELOP;
            }
"more_equal"        {
               BeginToken(yytext, &yyinlinePos);
               yylval.set(Ops::GreaterEq);
               return RELOP;
            }
"or"        {  BeginToken(yytext, &yyinlinePos); return OR;  }
"and"        {  BeginToken(yytext, &yyinlinePos); return AND;  }
"!"         {  BeginToken(yytext, &yyinlinePos); return NOT;  }

{id}        {
               BeginToken(yytext, &yyinlinePos);
               yylval.name = yytext;
               return NAME;
            }
{data}      {
               BeginToken(yytext, &yyinlinePos);
               std::string dat(yytext);
               yylval.set(dat);
               return DATA;
            }
{int}       {
               BeginToken(yytext, &yyinlinePos);
               yylval.set(atoi(yytext));
               return VALUE;
            }
.           {  
               BeginToken(yytext, &yyinlinePos);
               ScanError("Unexpected smth", yytext, yylineno);
               return ILLEGAL;  
            }
%%

int yywrap() { return 1; }

void ScanError(char const * s, char const * yytext, int lineno) {
  fprintf(stdout, "Scanner error: %s in line %d\n", s, lineno);
  fprintf(stdout, "%s\n", yytext);
}
