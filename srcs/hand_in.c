/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand_in.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 12:16:34 by amazurie          #+#    #+#             */
/*   Updated: 2017/03/15 14:15:50 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	chr_in(char **line, char *tmp, int **i)
{
	if ((*i)[2] > 2040)
		return ;
	(*i)[1] = 0;
	while ((*i)[1]++ < (*i)[4])
		ft_putchar('\b');
	(*i)[1] = 0;
	saddchr(line, tmp[0], (*i)[4]);
	ft_putstr(*line);
	ft_putstr(" \b");
	(*i)[2]++;
	(*i)[1] = (*i)[2];
	while (--(*i)[1] > (*i)[4])
		ft_putchar('\b');
	(*i)[4]++;
}

static void	del_in(char **line, int **i)
{
	if ((*i)[4] <= 0)
		return ;
	ft_putchar('\b');
	ft_putstr(((*line) + (*i)[4]));
	ft_putstr(" \b");
	ssupprchr(line, --(*i)[4]);
	(*i)[1] = (*i)[2];
	while (--(*i)[1] > (*i)[4])
		ft_putchar('\b');
	(*i)[2]--;
}

int			gest_in(t_hist *hist, char **line, char *tmp, int **i)
{
	if (tmp[0] == 4 && !**line)
		return (-1);
	else if (tmp[0] == 12)
	{
		free(*line);
		*line = ft_strdup("clear");
		(*i)[0] = 1;
	}
	else if (tmp[0] == 10)
		(*i)[0] = 1;
	else if (tmp[0] == 127 || tmp[0] == 8)
		del_in(line, i);
	else if (ft_isprint(tmp[0]))
		chr_in(line, &tmp[0], i);
	else
		gest_spekey(tmp, hist, i, line);
	return (0);
}
