#include "minishell.h"

int	*get_size(t_compl *c)
{
	struct winsize	w;
	int				*whcl;

	if (!(whcl = (int *)ft_memalloc(sizeof(int) * 9)))
		return (0);
	ioctl(0, TIOCGWINSZ, &w);
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

int		hand_arrow(t_compl *c, char *tmp)
{
	if ((tmp[0] == 27 && tmp[1] == 91 && ((tmp[2] == 65 && !tmp[3])
					|| (tmp[2] == 53 && tmp[3] == 126)))
			|| (tmp[0] == 16 && !tmp[1]))
		c->num_curr = (c->num_curr - 1 < 0) ? c->ac : c->num_curr - 1;
	else if ((tmp[0] == 27 && tmp[1] == 91 && ((tmp[2] == 66 && !tmp[3])
					|| (tmp[2] == 54 && tmp[3] == 126)))
			|| (tmp[0] == 14 && !tmp[1]))
		c->num_curr = (c->num_curr + 1 > c->ac) ? 0 : c->num_curr + 1;
//	else if (tmp[0] == 27 && tmp[1] == 91 && tmp[2] == 67 && !tmp[3])
//		hand_right();
//	else if (tmp[0] == 27 && tmp[1] == 91 && tmp[2] == 68 && !tmp[3])
//		hand_left();
	else
		return (0);
	return (2);
}

int		handle_compl(t_compl *c, char *tmp, int **i)
{
	if (tmp[0] == 10 && !tmp[1])
		return (1);
	else if (tmp[0] == 9 && !tmp[1])
		c->num_curr = (c->num_curr + 1 > c->ac) ? 0 : c->num_curr + 1;
	else
		return (hand_arrow(c, tmp));
	return (2);
}

int		do_select(t_compl *c, char **tmp, int **i)
{
	int	j;

	j = 2;
	while (j == 2)
	{
		read(0, *tmp, LIMIT_LINE);
		if (is_complsiged(0))
			return (-1);
//		int p = 0;
//		while (p < 6)
//			printf("%i\n", (*tmp)[p++]);
		if ((j = handle_compl(c, *tmp, i)) == 2)
			display_compl(c, i);
	}
	return (j);
}
