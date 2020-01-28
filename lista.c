#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>





int main( int argc, char *argv[])
{

DIR *dir;
struct  dirent *proxdir;
if (argc < 2){
dir = opendir(".");
}
else dir = opendir(argv[1]);

if (dir == NULL){
perror("erro no diretorio");
exit(1);
}


	while((proxdir = readdir(dir)) != NULL){ 
	printf("%s\n", proxdir->d_name);
	}
	
	
closedir(dir);
return(0);


}
