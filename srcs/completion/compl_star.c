#include "minishell.h"

int		compl_star(t_data **d, t_compl *c, char *word, int **i)
{
	t_arg	*ar;
	char	*tmp;
	char	*tmp2;

	if (c->is_star == 0)
		return (0);
	ssupprchr(&((*d)->line), (*i)[4] - 1);
	curs_left(d, i);
	(*i)[4]--;
	(*i)[2]--;
	ar = c->args;
	tmp = ft_strjoin(ar->elem, " ");
	while (ar && (ar = ar->next))
	{
		tmp2 = ft_strjoin(tmp, ar->elem);
		free(tmp);
		tmp = ft_strjoin(tmp2, " ");
		free(tmp2);
	}
	chr_in(d, tmp, i);
	free(tmp);
	return (1);
}
