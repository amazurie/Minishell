#include "minishell.h"

int		del_line(char **line, char *tmp, int **i)
{
	if (tmp[0] == 21)
	{
		(*i)[1] = 0;
		while ((*i)[1]++ < (*i)[4])
			ft_putchar('\b');
		ft_memset(*line, ' ', (*i)[2]);
		ft_putstr(*line);
		ft_memset(*line, '\b', (*i)[2]);
		ft_putstr(*line);
		ft_memset(*line, 0, (*i)[2]);
		(*i)[2] = 0;
		(*i)[3] = -1;
		(*i)[4] = 0;
		return (1);
	}
	return (0);
}
