#include "minishell.h"

void	hand_rigthcompl(t_compl *c, char *tmp)
{
	int	*whcl;

	whcl = get_size(c);
	whcl[6] = (whcl[4] > whcl[1]) ? whcl[1] : whcl[4];
	if (c->num_curr + whcl[6] > c->ac)
		while (c->num_curr - whcl[6] >= 0)
			c->num_curr -= whcl[6];
	else
		c->num_curr += (whcl[4] > whcl[1]) ? whcl[1] : whcl[4];
	free(whcl);
}

void	hand_leftcompl(t_compl *c, char *tmp)
{
	int	*whcl;

	whcl = get_size(c);
	whcl[6] = (whcl[4] > whcl[1]) ? whcl[1] : whcl[4];
	if (c->num_curr - whcl[6] < 0)
		while (c->num_curr + whcl[6] <= c->ac)
			c->num_curr += whcl[6];
	else
		c->num_curr -= whcl[6];
	free(whcl);
}

int		handle_compl(t_compl *c, char *tmp)
{
	if (tmp[0] == 10 && !tmp[1])
	{
		ft_bzero(tmp, ft_strlen(tmp));
		return (1);
	}
	else if (tmp[0] == 9 && !tmp[1])
		c->num_curr = (c->num_curr + 1 > c->ac) ? 0 : c->num_curr + 1;
	else if ((tmp[0] == 27 && tmp[1] == 91 && ((tmp[2] == 65 && !tmp[3])
					|| (tmp[2] == 53 && tmp[3] == 126)))
			|| (tmp[0] == 16 && !tmp[1]))
		c->num_curr = (c->num_curr - 1 < 0) ? c->ac : c->num_curr - 1;
	else if ((tmp[0] == 27 && tmp[1] == 91 && ((tmp[2] == 66 && !tmp[3])
					|| (tmp[2] == 54 && tmp[3] == 126)))
			|| (tmp[0] == 14 && !tmp[1]))
		c->num_curr = (c->num_curr + 1 > c->ac) ? 0 : c->num_curr + 1;
	else if ((tmp[0] == 27 && tmp[1] == 91 && tmp[2] == 67 && !tmp[3])
			|| (tmp[0] == 2 && !tmp[1]))
		hand_rigthcompl(c, tmp);
	else if ((tmp[0] == 27 && tmp[1] == 91 && tmp[2] == 68 && !tmp[3])
			|| (tmp[0] == 6 && !tmp[1]))
		hand_leftcompl(c, tmp);
	else
		return (0);
	return (2);
}

int		do_select(t_compl *c, char **tmp)
{
	int	j;

	j = 2;
	while (j == 2)
	{
		ft_bzero(*tmp, ft_strlen(*tmp));
		read(0, *tmp, LIMIT_LINE);
		if (is_siginted(0))
		{
			is_siginted(1);
			return (-1);
		}
		//		int p = 0;
		//		while (p < 6)
		//			printf("%i\n", (*tmp)[p++]);
		if ((j = handle_compl(c, *tmp)) == 2)
			display_compl(c);
	}
	return (j);
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
