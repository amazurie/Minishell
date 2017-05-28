#include "minishell.h"

int		handle_compl(t_compl *c, char *tmp, int **i)
{
	if (tmp[0] == 10 && !tmp[1])
		return (1);
	return (1);
}

int		do_select(t_compl *c, char **tmp, int **i)
{
	int	j;

	read(0, *tmp, LIMIT_LINE);
	if (is_complsiged(0))
		return (-1);
	int p = 0;
	while (p < 6)
		printf("%i\n", (*tmp)[p++]);
	return (handle_compl(c, *tmp, i));
}
