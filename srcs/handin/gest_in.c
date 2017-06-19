/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_in.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 12:30:47 by amazurie          #+#    #+#             */
/*   Updated: 2017/06/19 10:57:07 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if ((*i)[6] == 0 && (*d)->is_term == 1)
			display_prompt();
		else if ((*d)->is_term == 1)
			ft_putstr_fd((*d)->prompt, 0);
		ft_putstr_fd(((*d)->line + (*i)[6]), 0);
	}
	else if (tmp[0] == 10 && !tmp[1])
		quote(d, i);
	else
		return (gest_in2(d, tmp, i));
	return (0);
}
