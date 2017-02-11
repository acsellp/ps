
#include "get_next_line.h"

void swap(char **dest, char **src, int *sz, int *x)
{
	*dest = (char*)ft_memalloc(sizeof(char) * *sz);
	ft_memcpy(*dest, *src, *x);
	ft_memdel((void**)src);
}

void read_line(t_line_param *ln, char **line, int fd)
{
	ln->x = 0;
	while ((ln->ret = read(fd, &ln->c, BUFF_SIZE)))
	{
		if (ln->c == '\n' || ln->ret == -1)
			break;
		if (ln->x == ln->sz - 1)
		{
			swap(&ln->tmp, &ln->cpy, &ln->sz, &ln->x);
			ln->sz += TEMP_SIZE;
			swap(&ln->cpy, &ln->tmp, &ln->sz, &ln->x);
		}
		ft_strcat(ln->cpy, &ln->c);
		ln->cpy[ln->x + 1] = '\0';
		ln->x++;
	}
	*line = (char *)ft_memalloc(sizeof(char) * (ln->x + 1));
	ft_memcpy(*line, ln->cpy, ln->x);
}

int get_next_line(int fd, char **line)
{
	static int		stat;
	t_line_param	ln;

	stat = 0;
	if (line == NULL || fd < 0)
		return (-1);
	ln.sz = TEMP_SIZE;
	ln.cpy = (char*)ft_memalloc(sizeof(char) * ln.sz);
	ft_memset(ln.cpy, 0, ln.sz);
	read_line(&ln, line, fd);
	if (ln.ret == 0 && *ln.cpy)
	{
		stat = 1;
		return (1);
	}
	else
	{
		stat++;
		return (ln.ret);
	}
}
