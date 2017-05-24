/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 16:18:49 by amazurie          #+#    #+#             */
/*   Updated: 2017/05/24 16:18:55 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_open(t_data **d)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while ((*d)->line[k])
	{
		if ((*d)->line[k] == 34 && j != 2)
		{
			if (j == 0)
				j = 1;
			else
				j = 0;
		}
		else if ((*d)->line[k] == 39 && j != 1)
		{
			if (j == 0)
				j = 2;
			else
				j = 0;
		}
		k++;
	}
	return (j);
}

void		quote(t_data **d, int **i)
{
	int	j;

	j = check_open(d);
	if (j == 1 || j == 2)
	{
		free((*d)->prompt);
		ft_putchar_fd('\n', 0);
		if (j == 1)
			(*d)->prompt = ft_strdup("dquote> ");
		else
		(*d)->prompt = ft_strdup("quote> ");
		ft_putstr_fd((*d)->prompt, 0);
	}
	else
		(*i)[0] = 1;
	(*i)[6] = (*i)[2];
	(*i)[4] = (*i)[2];
	(*i)[3] = -1;
	(*i)[5] = 0;
}
