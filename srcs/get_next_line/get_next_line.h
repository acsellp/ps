
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#define BUFF_SIZE 1
#define TEMP_SIZE 1000

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "libft.h"

typedef struct	s_line_param
{
	int			x;
	int			sz;
	int			ret;
	char		c;
	char		*cpy;
	char		*tmp;
}				t_line_param;

int get_next_line(int fd, char **line);

#endif
