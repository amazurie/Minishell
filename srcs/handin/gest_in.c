/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_in.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 12:30:47 by amazurie          #+#    #+#             */
/*   Updated: 2017/06/07 12:45:01 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		chr_in(t_data **d, char *tmp, int **i)
{
	int	j;

	j = -1;
	while (tmp[++j])
	{
		ft_putstr_fd(tgetstr("sc", NULL), 0);
		erase_printline(d, i);
		if ((*i)[2] > LIMIT_LINE - 1)
		{
			maxline(d, tmp, i);
			return ;
		}
		saddchr(&((*d)->line), tmp[j], (*i)[4]);
		ft_putstr_fd(((*d)->line + (*i)[6]), 0);
		ft_putstr_fd(tgetstr("rc", NULL), 0);
		curs_right(d, i);
		(*i)[2]++;
		(*i)[4]++;
		(*i)[5] = 1;
	}
}

void		del_in(t_data **d, int **i)
{
	if ((*i)[4] <= (*i)[6])
		return ;
	ft_putstr_fd(tgetstr("sc", NULL), 0);
	erase_printline(d, i);
	ssupprchr(&((*d)->line), (*i)[4] - 1);
	ft_putstr_fd(((*d)->line + (*i)[6]), 0);
	ft_putstr_fd(tgetstr("rc", NULL), 0);
	curs_left(d, i);
	(*i)[2]--;
	(*i)[4]--;
	(*i)[5] = 1;
}

static int	gest_in2(t_data **d, char *tmp, int **i)
{
	if ((tmp[0] == 127 || tmp[0] == 8) && !tmp[1])
	{
		del_in(d, i);
		if (!(*d)->line[0])
			(*i)[5] = 0;
	}
	else if (ft_strisprint(tmp))
	{
		chr_in(d, &tmp[0], i);
		(*i)[5] = 1;
	}
	else
		return (gest_spekey(tmp, d, i));
	return (0);
}

int			gest_in(t_data **d, char *tmp, int **i)
{
	if (tmp[0] == 4 && !tmp[1] && !*(*d)->line)
		return (-1);
	else if (tmp[0] == 12 && !tmp[1])
	{
		ft_putstr_fd(tgetstr("cl", NULL), 0);
		if ((*i)[6] == 0)
			display_prompt();
		else
			ft_putstr_fd((*d)->prompt, 0);
		ft_putstr_fd(((*d)->line + (*i)[6]), 0);
	}
	else if (tmp[0] == 10 && !tmp[1])
		quote(d, i);
	else
		return (gest_in2(d, tmp, i));
	return (0);
}
