/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 12:20:21 by amazurie          #+#    #+#             */
/*   Updated: 2017/06/19 11:19:20 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	curs_right(t_data **d, int **i)
{
	struct winsize	w;
	int				j;

	ioctl(0, TIOCGWINSZ, &w);
	j = ft_strlen((*d)->prompt) + (*i)[4] - (*i)[6];
	while (j > w.ws_col)
		j -= w.ws_col;
	if (j == w.ws_col - 1)
		ft_putstr_fd(tgetstr("do", NULL), 0);
	else
		ft_putstr_fd(tgetstr("nd", NULL), 0);
}

void	curs_left(t_data **d, int **i)
{
	struct winsize	w;
	int				j;

	ioctl(0, TIOCGWINSZ, &w);
	j = ft_strlen((*d)->prompt) + (*i)[4] - (*i)[6];
	while (j > w.ws_col)
		j -= w.ws_col;
	if (j == w.ws_col)
	{
		ft_putstr_fd(tgetstr("up", NULL), 0);
		while (j-- > 0)
			ft_putstr_fd(tgetstr("nd", NULL), 0);
	}
	else
		ft_putstr_fd(tgetstr("le", NULL), 0);
}
