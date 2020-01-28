%{ 
   #include <stdio.h>
   #include "commands.h"
   #include "grammar.tab.h"
   int yylex();
   int yyerror(char*);
%}

%union {

   argStruct *ficheiros;
   command *comandos;
   Value *value;
   char *str;

}

%token MAKE MOS ACR APA INFO LIST 
%token<str> VAR_VALUE VAR_ARG VAR_NAME

%type<ficheiros> arg argList
%type<comandos> command commandList
%type<value> value

%%

program : commandList { Draw($1); }

commandList
  : command              { $$ = $1; }
  | command commandList  { $1->next = $2; $$ = $1; }
  ;

command
  : MOS argList           { $$ = insert_Mostra( NULL, $2 ); }
  | ACR argList           { $$ = insert_Acrescenta(NULL, $2); }
  | APA argList           { $$ = insert_Apaga(NULL, $2); }
  | INFO argList          { $$ = insert_Informa(NULL, $2); }
  | LIST argList          { $$ = insert_Lista(NULL, $2); }
  | VAR_NAME value        { $$ = insert_Make(NULL, $1, $2) ; }
  ;

argList
  : arg                     { $$ = $1; }
  | arg argList             { $1->next = $2; $$ = $1; }
  ;

arg
  : VAR_ARG { $$ = insert_Args(NULL, $1); }
  ;

value
  : VAR_VALUE	{ $$ = new_var_value($1); }
  ; 



%%

int yyerror(char* msg) {
    printf("ERROR: %s\n", msg);
    return 0;
}
