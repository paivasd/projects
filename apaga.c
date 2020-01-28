#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main( int argc, char *argv[])
{
	int fd, valor;
	valor = unlink(argv[1]);
	if(valor == -1)
	perror("erro ao eliminar ficheiro");

	return 0;
}

