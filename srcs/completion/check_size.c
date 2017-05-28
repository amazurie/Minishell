#include "minishell.h"

static int	check_up(int num_curr, int min_line, int *whcl)
{
	int	i;
	int	j;

	j = min_line;
	while (j-- > 0)
	{
		i = 0;
		while (i < whcl[3])
		{
			if (num_curr >= j + whcl[4] * i
					&& num_curr <= j + whcl[4] * i + whcl[1])
				return (j);
			i++;
		}
	}
	return (0);
}

static int	check_down(int num_curr, int min_line, int *whcl)
{
	int	i;
	int	j;

	j = min_line;
	while (j++ < whcl[4] - whcl[1])
	{
		i = 0;
		while (i < whcl[3])
		{
			if (num_curr >= j + whcl[4] * i
					&& num_curr <= j + whcl[4] * i + whcl[1])
				return (j);
			i++;
		}
	}
	return (0);
}


int			check_winsize(t_compl *c, int *whcl)
{
	int		i;
	int		j;

	i = 0;
	j = c->min_line;
	while (i < whcl[3])
	{
		if (c->num_curr >= j + whcl[4] * i
				&& c->num_curr < j + whcl[4] * i + whcl[1])
			return (j);
		i++;
	}
	if ((i = check_down(c->num_curr, c->min_line, whcl)) > 0)
		return (i);
	return (check_up(c->num_curr, c->min_line, whcl));
}

int		nbrline(t_arg *arg, int w, int *len)
{
	t_arg	*tmp;
	int		i;

	tmp = arg;
	i = 0;
	*len = 0;
	while (tmp)
	{
		if (ft_strlen(tmp->elem) >= (size_t)*len)
			*len = ft_strlen(tmp->elem) + 1;
		tmp = tmp->next;
		i++;
	}
	if (w > *len && i != 1)
		return (w / *len - (w % *len == 0));
	return (1);
}

int		nbr_col(t_arg *arg, int *nline)
{
	t_arg	*tmp;
	int		nbr;
	int		i;
	int		j;

	nbr = 0;
	tmp = arg;
	while (tmp)
	{
		tmp = tmp->next;
		nbr++;
	}
	i = 0;
	while (i * nbr < *nline)
		i++;
	j = nbr + (*nline - (i - 1) * nbr);
	i = 0;
	while (i * *nline < j)
		i++;
	i--;
	j = i + (i * *nline < nbr);
	*nline -= (i * *nline < nbr);
	return (i + (i * *nline < nbr));
}
