#include "minishell.h"

int		complet_arg(t_compl *c, char **tmp)
{
	int	j;

	j = 0;
	display_compl(c);
	j = 2;
	read(0, *tmp, LIMIT_LINE);
	if (is_siginted(0))
	{
		is_siginted(1);
		return (-1);
	}
	if ((*tmp)[0] == 9 && !(*tmp)[1])
	{
		c->num_curr = 0;
		display_compl(c);
		j = do_select(c, tmp);
	}
	return (j);
}
