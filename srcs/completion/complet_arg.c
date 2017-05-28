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

static int	*get_size(t_compl *c)
{
	struct winsize	w;
	int				*whcl;

	if (!(whcl = (int *)ft_memalloc(sizeof(int) * 9)))
		return (0);
	ioctl(0, TIOCGWINSZ, &w);
	c->num_curr = c->ac;
	whcl[0] = w.ws_col;
	whcl[1] = w.ws_row - 1;
	if (!(c->nbr_line) || !(c->nbr_line))
	{
		whcl[3] = nbrline(c->args, whcl[0], &whcl[2]);
		whcl[4] = nbr_col(c->args, &whcl[3]);
		c->nbr_line = whcl[3];
		c->nbr_col = whcl[4];
	}
	else
	{
		whcl[3] = c->nbr_line;
		whcl[4] = c->nbr_col;
	}
	whcl[5] = check_winsize(c, whcl);
	c->min_line = whcl[5];
	return (whcl);
}

int		complet_arg(t_compl *c, char **tmp, int **i)
{
	int	*whcl;
	int	j;

	whcl = get_size(c);
	j = 0;
	while (j++ < whcl[5])
		ft_putstr_fd(tgetstr("nd", NULL), 0);
	display_all(c, whcl, i);
	free(whcl);
	j = 2;
	signal(SIGINT, sig_compl);
	while (j == 2)
		j = do_select(c, tmp, i);
	signal(SIGINT, sighandler);
	return (0);
}
