#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>

int main( int argc, char *argv[])
{
	int fd;
	char buffer[900];

	fd = open(argv[1], O_RDONLY);
	if (fd == -1){
		perror("erro na abertura");
		return(-1);

	}
	read(fd, buffer, sizeof(buffer));

	close(fd);

	printf("Conteudo do ficheiro:\n%s\n", buffer);
	
}

