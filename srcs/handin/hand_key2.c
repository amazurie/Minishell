/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand_key2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 16:07:48 by amazurie          #+#    #+#             */
/*   Updated: 2017/05/24 16:18:28 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	endhome_key(char *tmp, int **i, char **line)
{
	if ((tmp[0] == 27 && tmp[1] == 91 && (tmp[2] == 72 || tmp[2] == 70))
			|| ((tmp[0] == 1 || tmp[0] == 5) && !tmp[1]))
	{
		if (tmp[2] == 72 || tmp[0] == 1)
		{
			while ((*i)[4]-- > (*i)[6])
				ft_putstr_fd(tgetstr("le", NULL), 0);
			(*i)[4] = 0;
			return (1);
		}
		ft_putstr_fd(((*line) + (*i)[4] + (*i)[6]), 0);
		(*i)[4] = (*i)[2];
		return (1);
	}
	return (0);
}

int			del_key(char *tmp, int **i, t_data **d)
{
	if ((tmp[0] == 27 && tmp[1] == 91 && tmp[2] == 51)
			|| (tmp[0] == 4 && !tmp[1]))
	{
		if ((tmp[0] == 4 || tmp[3] == 126) && (*i)[4] < (*i)[2])
		{
			curs_right(d, i);
			(*i)[4]++;
			del_in(d, i);
		}
		return (1);
	}
	return (endhome_key(tmp, i, &((*d)->line)));
}

int			del_line(char **line, char *tmp, int **i)
{
	if (tmp[0] != 21 || tmp[1])
		return (0);
	while ((*i)[4]-- > (*i)[6])
		ft_putstr_fd(tgetstr("le", NULL), 0);
	ft_putstr_fd(tgetstr("cd", NULL), 0);
	ft_bzero((*line + (*i)[6]), (*i)[2] - (*i)[6]);
	(*i)[2] = (*i)[6];
	(*i)[3] = -1;
	(*i)[4] = (*i)[6];
	return (1);
}
