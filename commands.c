#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

Value *new_name(char *v) {
	//printf("new name");
    	Value *val = (Value*) malloc(sizeof(Value));
    	val->variableN = v;
    	//printf("\nnew name %s", val->variableN);
        //printf("\ncheckpoint 2");
    	return val;
}

Value *new_var_value(char *v) {
    	Value *val = (Value*) malloc(sizeof(Value));
    	val->variableV = v;
	    
        //printf("\nvalor variavel: %s", val->variableV);
        
        //printf("\ncheckpoint 1");
    	return val;
        
}

/*Value *vars (char *v) 
{
	Value *valores = (Value*) malloc(sizeof(Value));
	valores->variableV = v;
	return valores;
}*/

Terminal *new_terminal() 
{
    Terminal *terminal = (Terminal*) malloc(sizeof(Terminal));
    terminal-> vars = NULL; // no variables in the beginning
    return terminal;
}


char * findVar(SymbolTable *vars, char* variable) {
    if (vars == NULL) {
        fprintf(stderr, "Variable %s undefined!\n", variable);
        exit(1);
    }
    if (strcmp(vars->variableName, variable) == 0) {
        return vars->variableValue;
    }
    else {
        return findVar(vars->next, variable);
    }
}


SymbolTable * updateVar(SymbolTable *vars, char *variableN, char *variableV) {
    if (vars == NULL) {
        //printf("\ncheckpoint 3");
        SymbolTable *node = (SymbolTable*) malloc(sizeof(SymbolTable));
        node->variableName = strdup(variableN); // keep a fresh copy of the variable name
        node->variableValue = strdup(variableV);
        node->next = NULL;
        return node;
    }
    else {
        if (strcmp(vars->variableName, variableN) == 0) {
            //printf("\ncheckpoint 4");
            vars->variableValue = variableV;
            return vars;
        } else {
            //printf("\ncheckpoint 5");
            vars->next = updateVar(vars->next, variableN, variableV);
            return vars;
        }
    }
}


void ExecuteCommands(Terminal *terminal, command *lst) {
    if (!lst) return;   // no list, no fun!
    switch(lst->type) {
        case MK:
            // arg1 => nome da variavel
            // arg2 => valor da variavel
            {
              //printf("v nome: %s | v value: %s", lst->arg1->variableN, lst->arg2->variableV);
              terminal->vars = updateVar(terminal->vars, lst->arg1->variableN, lst->arg2->variableV);
              //printf("nomev: %s variabl v: %s", lst->arg1->variableN, lst->arg2->variableV);
            }
            break;
        case MOSTRA:
            // 360 -- 2*PI
            // arg1 -- ?
            {
                if(terminal->vars != NULL)
                {
                    while(terminal->vars->next!=NULL)
                    {

                        pid_t pid = fork(); // implementar aceitação varios argumentos, verificar break; neste caso (para nao executar todas as vezes)
				        if (pid == 0) 
				        {
                            //printf("%s, %s", terminal->vars->variableName, terminal->vars->variableValue); 
                            char *args[3];
					        args[0] = strdup("mostra");
					        args[1] = strdup(terminal->vars->variableValue);
					        args[2] = NULL;
					        //printf("\n%s %s %s\n ", args[0], args[1], args[2]);
		
					        execv(args[0],args);

                        }
                        else
                        {
                            waitpid(pid,0,0);
                        }
                        terminal->vars = terminal->vars->next;
                    }
                    if(terminal->vars->next == NULL)
                    {
                        pid_t pid = fork(); // implementar aceitação varios argumentos, verificar break; neste caso (para nao executar todas as vezes)
				        if (pid == 0) 
				        {
                                //printf("%s, %s", terminal->vars->variableName, terminal->vars->variableValue); 
                                char *args[3];
					            args[0] = strdup("mostra");
					            args[1] = strdup(terminal->vars->variableValue);
					            args[2] = NULL;
					            //printf("\n%s %s %s\n ", args[0], args[1], args[2]);
		
					            execv(args[0],args);

                        }
                        else
                        {
                            waitpid(pid,0,0);
                        }
                    }break;
                    
                }
                
                
                while(lst->argList->next != NULL)
                {

                    pid_t pid = fork();
				    if (pid == 0) 
				    {

                        char *args[3];
					    args[0] = strdup("mostra");
					    args[1] = strdup(lst->argList->nomeFicheiro);
					    args[2] = NULL;
					    //printf("\n%s %s %s\n ", args[0], args[1], args[2]);
		
		
					    execv(args[0],args);
                    }
                    else
                    {
                        waitpid(pid,0,0);
                    }
					//printf("\nexecutou\n");
                    lst->argList = lst->argList->next;
                    //printf("%s", strdup(lst->argList->nomeFicheiro));

                    
                }
                if (lst->argList->next == NULL)
                {
                    pid_t pid = fork();
				    if (pid == 0) 
				    {

                        char *args[3];
					    args[0] = strdup("mostra");
					    args[1] = strdup(lst->argList->nomeFicheiro);
					    args[2] = NULL;
					    //printf("\n%s %s %s\n ", args[0], args[1], args[2]);
		
		
					    execv(args[0],args);
                    }
                    else
                    {
                        waitpid(pid,0,0);
                    }
                }
            }
            break;
        case ACRESCENTA:
            {
              char *aux;
              aux = strdup(lst->argList->nomeFicheiro);
              while(lst->argList->next != NULL)
                {
                    
                    pid_t pid = fork();
				    if (pid == 0) 
				    {
                        
                        char *args[4];
					    args[0] = strdup("acrescenta");
					    args[1] = aux;
					    args[2] = strdup(lst->argList->next->nomeFicheiro);
                        args[3] = NULL;
					    printf("\n%s %s %s %s\n ", args[0], args[1], args[2], args[3]);
		
		
					    execv(args[0],args);
                    }
                    else
                    {
                        waitpid(pid,0,0);
                    }
					
                    lst->argList = lst->argList->next;
                    printf("%s", strdup(lst->argList->nomeFicheiro));

                }
                /*if (lst->argList->next == NULL){
                    pid_t pid = fork();
				    if (pid == 0) 
				    {

                        char *args[4];
					    args[0] = "acrescenta";
					    args[1] = aux;
					    args[2] = lst->argList->nomeFicheiro;
                        args[3] = NULL;
					    printf("\n%s %s %s %s\n ", args[0], args[1], args[2], args[3]);
		
		
					    execv(args[0],args);
                    }
                    else
                    {
                        waitpid(pid,0,0);
                    }
                }*/
            }
            break;

        case APAGA:
            {
              while(lst->argList->next != NULL)
                {

                    pid_t pid = fork();
				    if (pid == 0) 
				    {

                        char *args[3];
					    args[0] = strdup("apaga");
					    args[1] = lst->argList->nomeFicheiro;
					    args[2] = NULL;
					    printf("\n%s %s %s\n ", args[0], args[1], args[2]);
		
		
					    execv(args[0],args);
                    }
                    else
                    {
                        waitpid(pid,0,0);
                    }
					//printf("\nexecutou\n");
                    lst->argList = lst->argList->next;
                    printf("%s", strdup(lst->argList->nomeFicheiro));
                }
                if (lst->argList->next == NULL)
                {
                    pid_t pid = fork();
				    if (pid == 0) 
				    {

                        char *args[3];
					    args[0] = strdup("apaga");
					    args[1] = strdup(lst->argList->nomeFicheiro);
					    args[2] = NULL;
					    printf("\n%s %s %s\n ", args[0], args[1], args[2]);
		
		
					    execv(args[0],args);
                    }
                    else
                    {
                        waitpid(pid,0,0);
                    }
                }
            }
            break;

        case INFORMA:
            {
               while(lst->argList->next != NULL)
                {

                    pid_t pid = fork();
				    if (pid == 0) 
				    {

                        char *args[3];
					    args[0] = strdup("informa");
					    args[1] = lst->argList->nomeFicheiro;
					    args[2] = NULL;
					    printf("\n%s %s %s\n ", args[0], args[1], args[2]);
		
		
					    execv(args[0],args);
                    }
                    else
                    {
                        waitpid(pid,0,0);
                    }
					//printf("\nexecutou\n");
                    lst->argList = lst->argList->next;
                    printf("%s", strdup(lst->argList->nomeFicheiro));
                }
                if (lst->argList->next == NULL)
                {
                    pid_t pid = fork();
				    if (pid == 0) 
				    {

                        char *args[3];
					    args[0] = strdup("informa");
					    args[1] = strdup(lst->argList->nomeFicheiro);
					    args[2] = NULL;
					    printf("\n%s %s %s\n ", args[0], args[1], args[2]);
		
		
					    execv(args[0],args);
                    }
                    else
                    {
                        waitpid(pid,0,0);
                    }
                }           
            }
            break;

        case LISTA:
            {
               while(lst->argList->next != NULL)
                {

                    pid_t pid = fork();
				    if (pid == 0) 
				    {

                        char *args[3];
					    args[0] = strdup("lista");
					    args[1] = lst->argList->nomeFicheiro;
					    args[2] = NULL;
					    printf("\n%s %s %s\n ", args[0], args[1], args[2]);
		
		
					    execv(args[0],args);
                    }
                    else
                    {
                        waitpid(pid,0,0);
                    }
					//printf("\nexecutou\n");
                    lst->argList = lst->argList->next;
                    printf("%s", strdup(lst->argList->nomeFicheiro));
                }
                if (lst->argList->next == NULL)
                {
                    pid_t pid = fork();
				    if (pid == 0) 
				    {

                        char *args[3];
					    args[0] = strdup("lista");
					    args[1] = strdup(lst->argList->nomeFicheiro);
					    args[2] = NULL;
					    printf("\n%s %s %s\n ", args[0], args[1], args[2]);
		
		
					    execv(args[0],args);
                    }
                    else
                    {
                        waitpid(pid,0,0);
                    }
                }
            }break;
    }
    ExecuteCommands(terminal, lst->next);
}



void Draw(command *lst) {
    Terminal *terminal = new_terminal();
    ExecuteCommands(terminal, lst);

}


command *insert_Mostra(command *lst, argStruct* ficheiros) {
    command *node = (command*) malloc(sizeof(command));
    node->type = MOSTRA;
    node->argList = ficheiros;
    node->subCommands = NULL;
    node->next = lst;
    return node;
}

command *insert_Acrescenta(command *lst, argStruct* ficheiros) {
    command *node = (command*) malloc(sizeof(command));
    node->type = ACRESCENTA;
    node->argList = ficheiros;
    node->subCommands = NULL;
    node->next = lst;
    return node;
}

command *insert_Apaga(command *lst, argStruct* ficheiros) {
    command *node = (command*) malloc(sizeof(command));
    node->type = APAGA;
    node->argList = ficheiros;
    node->subCommands = NULL;
    node->next = lst;
    return node;
}

command *insert_Informa(command *lst, argStruct* ficheiros) {
    command *node = (command*) malloc(sizeof(command));
    node->type = INFORMA;
    node->argList = ficheiros;
    node->subCommands = NULL;
    node->next = lst;
    return node;
}

command *insert_Conta(command *lst, argStruct* ficheiros) {
    command *node = (command*) malloc(sizeof(command));
    node->type = CONTA;
    node->argList = ficheiros;
    node->subCommands = NULL;
    node->next = lst;
    return node;
}

command *insert_Lista(command *lst, argStruct* ficheiros) {
    command *node = (command*) malloc(sizeof(command));
    node->type = LISTA;
    node->argList = ficheiros;
    node->subCommands = NULL;
    node->next = lst;
    return node;
}


argStruct *new_arg(char *v){
    argStruct *node = (argStruct*)malloc(sizeof(argStruct));
    node->nomeFicheiro = v;
    return node;
}

argStruct *insert_Args(argStruct *ficheiros, char *nomeFicheiro) {
   argStruct *node = (argStruct*)malloc(sizeof(argStruct));
   node->nomeFicheiro = strdup(nomeFicheiro);
   node->next = ficheiros;
   return node;
}


command *insert_Make(command *lst, char *var_name, Value *var_value) {
    command *node = (command*) malloc(sizeof(command));

    node->type = MK;
    node->arg1 = new_name(var_name);
    node->arg2 = var_value;
    node->next = lst;
    node->subCommands = NULL;

    return node;
}
