   #include "commands.h"
   #include "grammar.tab.h"
   
%%

make              { return MAKE; }

mostra            { return MOS; }

acrescenta        { return ACR; }

apaga             { return APA; }

informa           { return INFO;}

lista             { return LIST;}

[a-z.]+         { yylval.str = strdup(yytext); return VAR_ARG; } // argStrcut a funcionar bem

\$[a-z]+        { yylval.str = strdup(yytext+1); return VAR_NAME; }

\:[a-z]+         { yylval.str = strdup(yytext+1); return VAR_VALUE; }





[ \n\r\t]         { /* ignore */ }


.                 { return yytext[0]; }

%%

int yywrap() { return 1; }
