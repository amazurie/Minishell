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
		return (0);
	}
	if ((*tmp)[0] == 9 && !(*tmp)[1])
	{
		c->num_curr = 0;
		display_compl(c);
		signal(SIGINT, sig_compl);
		j = do_select(c, tmp);
		signal(SIGINT, sighandler);
	}
	return (j);
}
