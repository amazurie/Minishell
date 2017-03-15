/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand_in.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 12:16:34 by amazurie          #+#    #+#             */
/*   Updated: 2017/03/14 17:24:21 by amazurie         ###   ########.fr       */
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

static int	gest_in(h_list *hist, char **line, char *tmp, int **i)
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
	else if (tmp[0] == 127|| tmp[0] == 8)
		del_in(line, i);
	else if (ft_isprint(tmp[0]))
		chr_in(line, &tmp[0], i);
	else
		gest_spekey(tmp, hist, i, line);
	return (0);
}

int			in(h_list *hist, char **line)
{
	char	*tmp;
	int		*i;

	*line = (char *)ft_memalloc(2048);
	tmp = (char *)ft_memalloc(6);
	i = (int *)ft_memalloc(sizeof(int) * 5);
	i[0] = 0;
	i[3] = -1;
	while (i[0] == 0)
	{
		read(0, tmp, 5);
		//int pfrw = 0;
		//while (tmp[pfrw])
		//	printf("\ntyped: %i\n", tmp[pfrw++]);
		if (SIGINTED == 1)
		{
			ft_memset(*line, 0, i[2]);
			i[2] = 0;
			i[3] = -1;
			i[4] = 0;
			SIGINTED = 0;
		}
		if (tmp[0] == 4)
			i[0] = -1;
		if (gest_in(hist, line, tmp, &i) == -1)
			i[0] = -1;
		ft_bzero(tmp, 6);
	}
	free(tmp);
	free(i);
	return (i[0]);
}
