#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>
int main( int argc, char *argv[])
{

	int fd;
	char buffer[400];
	int lidos;
	int contador = 0;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1){
		perror("erro na abertura: ");
		exit(1);
	}
	lidos = read(fd, buffer, sizeof(buffer)); 
	for (int i = 0; i < lidos; i++){
		if(buffer[i] == '\n')
		contador++;

	}
	close(fd);
	printf("Linhas: %d\n", contador);
}
