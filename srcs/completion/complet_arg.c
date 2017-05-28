#include "minishell.h"

void		sig_compl(int sig)
{
	t_data	*d;

	if (sig == SIGINT)
	{
		ft_putstr_fd(tgetstr("cd", NULL), 0);
		is_complsiged(1);
		signal(SIGINT, sighandler);
	}
	else
		sighandler(sig);
}

int		complet_arg(t_compl *c, char **tmp, int **i)
{
	int	j;

	j = 0;
	display_compl(c, i);
	j = 2;
	read(0, *tmp, LIMIT_LINE);
	if (is_siginted(0))
	{
		is_siginted(1);
		return (0);
	}
	c->num_curr = 0;
	signal(SIGINT, sig_compl);
	if ((*tmp)[0] == 9 && !(*tmp)[1])
		display_compl(c, i);
	signal(SIGINT, sighandler);
	j = do_select(c, tmp, i);
	return (j);
}
