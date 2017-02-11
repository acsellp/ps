#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

int main(int ac, char **av)
{
	char *c;
	int fd;
	int r;

	fd = open(av[1], O_RDONLY);
	c = NULL;
	while((r = get_next_line(fd, &c)))
		 printf("%s(%d)\n", c,r);
	printf("\n\n%d\n",r);
	close(fd);
	(void)av;
	(void)ac;
	return (ac);
}
