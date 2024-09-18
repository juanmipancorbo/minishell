# include "../include/minishell.h"
# include <string.h>

int main(void)
{
	int fd[2];
	char buffer[100];
	char *test = "prueba fd";
	char *test2 = "--prueba fd";
	pipe(fd);
	write(fd[WRITE_END],test, strlen(test));
	read(fd[READ_END],buffer,sizeof(buffer));
	printf("%s\n",buffer);

	close(fd[WRITE_END]);
	close(fd[READ_END]);
	write(fd[WRITE_END],test2, strlen(test));
	int x = read(fd[READ_END],buffer,sizeof(buffer));
	printf("%d\n",x);
	printf("%s\n",buffer);
	return 0;

}