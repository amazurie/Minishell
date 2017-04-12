/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand_key2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 16:07:48 by amazurie          #+#    #+#             */
/*   Updated: 2017/04/12 10:32:54 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	endhome_key(char *tmp, int **i, char **line)
{
	if (tmp[2] == 72 || tmp[2] == 70 || tmp[0] == 1
			|| tmp[0] == 5)
	{
		if (tmp[2] == 72 || tmp[0] == 1)
		{
			(*i)[1] = 0;
			while ((*i)[1]++ < (*i)[4])
				ft_putchar('\b');
			(*i)[4] = 0;
			return (1);
		}
		ft_putstr(((*line) + (*i)[4]));
		(*i)[4] = (*i)[2];
		return (1);
	}
	return (0);
}

int			del_key(char *tmp, int **i, t_data **d)
{
	if (tmp[2] == 51 || tmp[0] == 4)
	{
		if ((tmp[0] == 4 || tmp[3] == 126) && (*i)[4] < (*i)[2])
		{
			ft_putchar((*d)->line[(*i)[4]]);
			(*i)[4]++;
			del_in(d, i);
		}
		return (1);
	}
	return (endhome_key(tmp, i, &((*d)->line)));
}

int			del_line(char **line, char *tmp, int **i)
{
	if (tmp[0] == 21)
	{
		(*i)[1] = 0;
		while ((*i)[1]++ < (*i)[4])
			ft_putchar('\b');
		ft_memset(*line, ' ', (*i)[2]);
		ft_putstr(*line);
		ft_memset(*line, '\b', (*i)[2]);
		ft_putstr(*line);
		ft_memset(*line, 0, (*i)[2]);
		(*i)[2] = 0;
		(*i)[3] = -1;
		(*i)[4] = 0;
		return (1);
	}
	return (0);
}
