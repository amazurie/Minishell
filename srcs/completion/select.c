/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 11:30:06 by amazurie          #+#    #+#             */
/*   Updated: 2017/06/13 10:04:52 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	compl_endhome(t_compl *c, char *tmp)
{
	int	*whcl;

	whcl = get_size(c);
	if ((tmp[0] == 27 && tmp[1] == 91 && (tmp[2] == 72 || tmp[2] == 70))
			|| ((tmp[0] == 1 || tmp[0] == 5) && !tmp[1]))
	{
		whcl[6] = 0;
		if (tmp[2] == 72 || tmp[0] == 1)
		{
			while (c->num_curr < whcl[4] * whcl[6]
					|| c->num_curr > whcl[4] * whcl[6] + whcl[4])
				whcl[6]++;
			c->num_curr = whcl[4] * whcl[6];
			free(whcl);
			return (2);
		}
		while (c->num_curr < whcl[4] * whcl[6]
				|| c->num_curr > whcl[4] * whcl[6] + whcl[4])
			whcl[6]++;
		c->num_curr = whcl[4] * whcl[6] + --whcl[4];
		free(whcl);
		return (2);
	}
	free(whcl);
	return (0);
}

static void	hand_rlcompl(t_compl *c, char *tmp)
{
	int	*whcl;

	if ((tmp[0] == 27 && tmp[1] == 91 && tmp[2] == 67 && !tmp[3])
			|| (tmp[0] == 2 && !tmp[1]))
	{
		whcl = get_size(c);
		if (c->num_curr + whcl[4] > c->ac && ++c->num_curr >= -1)
			while (c->num_curr - whcl[4] >= 0)
				c->num_curr -= whcl[4];
		else
			c->num_curr += whcl[4];
		free(whcl);
	}
	else
	{
		whcl = get_size(c);
		if (c->num_curr - whcl[4] < 0 && --c->num_curr >= -1)
			while (c->num_curr + whcl[4] <= c->ac)
				c->num_curr += whcl[4];
		else
			c->num_curr -= whcl[4];
		free(whcl);
	}
}

static int	handle_compl(t_compl *c, char *tmp)
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
	else if (((tmp[0] == 27 && tmp[1] == 91 && tmp[2] == 67 && !tmp[3])
			|| (tmp[0] == 2 && !tmp[1])) ||
			((tmp[0] == 27 && tmp[1] == 91 && tmp[2] == 68 && !tmp[3])
			|| (tmp[0] == 6 && !tmp[1])))
		hand_rlcompl(c, tmp);
	else
		return (compl_endhome(c, tmp));
	return (2);
}

static int	do_select(t_compl *c, char **tmp)
{
	int	j;

	j = 2;
	while (j == 2)
	{
		ft_bzero(*tmp, ft_strlen(*tmp));
		read(0, *tmp, LIMIT_LINE);
		if (is_siginted(0))
			return (-1);
		if ((j = handle_compl(c, *tmp)) == 2)
			display_compl(c);
	}
	return (j);
}

int			complet_arg(t_compl *c, char **tmp)
{
	int	j;

	c->min_line = 0;
	if (c->ac == 0)
	{
		c->word = c->args->elem;
		c->num_curr = 0;
		display_compl(c);
		return (0);
	}
	c->num_curr = -1;
	display_compl(c);
	read(0, *tmp, LIMIT_LINE);
	if (is_siginted(0))
		return (-1);
	if ((*tmp)[0] != 9 || (*tmp)[1])
		return (0);
	c->num_curr = 0;
	display_compl(c);
	j = do_select(c, tmp);
	return (j);
}
