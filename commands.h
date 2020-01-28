
typedef struct _value {  
    char *variableN; // variable name
    char *variableV; // variable value
} Value;

Value *new_var_declaration(char *n);

typedef struct _symbolTable {
    char *variableName;
    char *variableValue;
    struct _symbolTable* next;
} SymbolTable;

typedef struct _terminal {
    SymbolTable *vars;
} Terminal;

Terminal *new_terminal();

typedef enum {
    MOSTRA, ACRESCENTA, APAGA, MK, INFORMA, LISTA, CONTA
} commandType;

typedef struct _argStruct {

    char *nomeFicheiro;

    struct _argStruct * next;

} argStruct;

typedef struct _command {

   commandType type;   // nome do comando (tipo) 
   Value* arg1;           // 1o argumento (keep? change?)
   Value* arg2;           // 2o argumento
   argStruct* argList;

   struct _command * subCommands; // no caso do repeat, os elementos "internos"
   struct _command * next;  // next command

} command;

command *insert_Make(command *lst, char *var_name, Value *var_value);
command *insert_Mostra(command *lst, argStruct* ficheiros);
command *insert_Acrescenta(command *lst, argStruct* ficheiros);
command *insert_Apaga(command *lst, argStruct* ficheiros);
command *insert_Informa(command *lst, argStruct* ficheiros);
command *insert_Lista(command *lst, argStruct* ficheiros);
command *insert_Conta(command *lst, argStruct* ficheiros);
//command *insert_RotateRight(command *lst, Value* graus);
void DebugCommands(command *lst);
void Draw(command *lst);
SymbolTable * updateVar(SymbolTable *vars, char *variableN, char *variableV);
char * findVar(SymbolTable *vars, char *variableN);
Value *vars (char *v);
Value *new_var_value(char *v);
Value *new_name(char *v);
void ExecuteCommands(Terminal *terminal, command *lst);
argStruct *insert_Args(argStruct *ficheiros, char *nomeFicheiro);
argStruct *new_arg(char *v);

