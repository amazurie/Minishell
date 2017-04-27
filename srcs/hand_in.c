/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand_in.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 12:16:34 by amazurie          #+#    #+#             */
/*   Updated: 2017/04/12 11:36:39 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	chr_in(t_data **d, char *tmp, int **i)
{
	char	*temp;
	size_t	j;

	if ((*i)[2] > 2040)
		maxline(&((*d)->line), i);
	j = ft_strlen((*d)->prompt) + 3;
	(*i)[1] = 0;
	while ((*d)->line[(*i)[1]])
		if ((*d)->line[(*i)[1]++] == '\t')
			j += 7;
	(*i)[1] = 0;
	temp = (char *)ft_memalloc((*i)[2] + j + 1);
	ft_memset(temp, ' ', (*i)[2] - (*i)[4]);
	ft_putstr_fd(temp, 0);
	ft_memset(temp, '\b', j + (*i)[2]);
	ft_putstr_fd(temp, 0);
	display_prompt();
	saddchr(&((*d)->line), tmp[0], (*i)[4]);
	ft_putstr_fd((*d)->line, 0);
	(*i)[2]++;
	ft_memset(temp, 0, j + (*i)[2]);
	ft_memset(temp, '\b', (*i)[2] - (*i)[4] - 1);
	ft_putstr_fd(temp, 0);
	(*i)[4]++;
	free(temp);
}

void		del_in(t_data **d, int **i)
{
	char	*temp;
	size_t	j;

	if ((*i)[4] <= 0)
		return ;
	j = ft_strlen((*d)->prompt) + 3;
	(*i)[1] = 0;
	while ((*d)->line[(*i)[1]])
		if ((*d)->line[(*i)[1]++] == '\t')
			j += 7;
	(*i)[1] = 0;
	temp = (char *)ft_memalloc((*i)[2] + j + 1);
	ft_memset(temp, '\b', j + (*i)[4]);
	ft_putstr_fd(temp, 0);
	ft_memset(temp, ' ', j + (*i)[2]);
	ft_putstr_fd(temp, 0);
	ft_memset(temp, '\b', j + (*i)[2]);
	ft_putstr_fd(temp, 0);
	display_prompt();
	ssupprchr(&((*d)->line), --(*i)[4]);
	ft_putstr_fd((*d)->line, 0);
	ft_memset(temp, 0, j + (*i)[2]);
	ft_memset(temp, '\b', (*i)[2]-- - (*i)[4] - 1);
	ft_putstr_fd(temp, 0);
	free(temp);
}

int			gest_in(t_data **d, char *tmp, int **i)
{
	if (tmp[0] == 4 && !*(*d)->line)
		return (-1);
	else if (tmp[0] == 12)
	{
		ft_putstr("\033c");
		display_prompt();
		ft_putstr_fd((*d)->line, 0);
	}
	else if (tmp[0] == 10)
		(*i)[0] = 1;
	else if (tmp[0] == 127 || tmp[0] == 8)
	{
		del_in(d, i);
		if (!(*d)->line[0])
			(*i)[5] = 0;
	}
	else if (ft_isprint(tmp[0]) || (tmp[0] == 9
				&& is_onlytab((*d)->line)))
	{
		chr_in(d, &tmp[0], i);
		(*i)[5] = 1;
	}
	else
		gest_spekey(tmp, d, i);
	return (0);
}
