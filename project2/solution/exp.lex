%option noyywrap

%{
#include <cstdio>
#include <iostream>
#include <string>


#define YYSTYPE std::string
#include "exp.tab.h"
%}

alpha [A-Za-z]
num [0-9]
ident [0-9a-zA-Z_]


id ({alpha}|_){ident}*
intv {num}+
floatv {intv}\.{intv}
 
%%
{id} { yylval = std::string(yytext);
return ID; }

{intv} { yylval = std::string(yytext);
return INTV;}

{floatv} {
yylval = std::string(yytext);
return FLOATV;}

"=" { return EQ;
}

"+" { return PLUS;
}

"-" { return MINUS;
}

"*" { return MUL;
}

"//" { return IDIV;

}

"/" { return DIV;
}

"%" { return MOD;
}

[ \t\r\n]+ 

. {return yytext[0];}

%%

void scan_string(const char *s){
    yy_scan_string(s);
}
void delete_buffer(){
    yy_delete_buffer(YY_CURRENT_BUFFER);
}