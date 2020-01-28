#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>



int main( int argc, char *argv[]){

struct stat buffer;
stat(argv[1], &buffer);
printf("Tamanho do ficheiro = %ld\n", buffer.st_size);
switch (buffer.st_mode & S_IFMT){ // documentação exemplo man 2 stat
case S_IFDIR: printf("O ficheiro é uma diretoria\n"); break; 
case S_IFREG: printf("O ficheiro é um ficheiro normal\n"); break;
case S_IFLNK: printf("O ficheiro é um soft link\n"); break;
case S_IFSOCK: printf("O ficheiro é uma socket\n"); break;
case S_IFIFO: printf("O ficheiro é um ficheiro FIFO\n"); break;
default: printf("Desconhecido?\n");
}
printf("i-node = %ld\n", buffer.st_ino);
printf("Utilizador dono = %d\n", buffer.st_uid);
printf("Data ultima modificação: = %ld\n", buffer.st_mtime);
return 0;


}
