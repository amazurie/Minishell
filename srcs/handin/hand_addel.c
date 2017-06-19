/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand_addel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 10:58:04 by amazurie          #+#    #+#             */
/*   Updated: 2017/06/19 10:58:52 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_curspos(t_data **d, int **i)
{
	struct winsize	w;
	int				j;

	ioctl(0, TIOCGWINSZ, &w);
	j = ft_strlen((*d)->prompt) + (*i)[2] - (*i)[6];
	while (j > w.ws_col)
		j -= w.ws_col;
	if (j == w.ws_col)
		ft_putstr_fd(tgetstr("do", NULL), 0);
}

static	int	adding(t_data **d, char *tmp, int **i)
{
	int	j;

	j = -1;
	while (tmp[++j])
	{
		if ((*i)[2] > LIMIT_LINE - 1)
			maxline(d, tmp, i);
		if ((*i)[2] > LIMIT_LINE - 1)
			return (-1);
		saddchr(&((*d)->line), tmp[j], (*i)[4] + j);
		(*i)[2]++;
		if ((*d)->is_term == 0)
			ft_putchar_fd(tmp[j], 0);
	}
	return (j);
}

void		chr_in(t_data **d, char *tmp, int **i)
{
	int	j;
	int	i4;

	(*i)[5] = 1;
	if ((*d)->is_term == 1)
		erase_printline(d, i);
	if ((j = adding(d, tmp, i)) == -1)
		return ;
	if ((*d)->is_term == 1)
		ft_putstr_fd(((*d)->line + (*i)[6]), 0);
	check_curspos(d, i);
	i4 = (*i)[4] + j;
	(*i)[4] = (*i)[2];
	while (i4++ < (*i)[2])
	{
		curs_left(d, i);
		(*i)[4]--;
	}
}

void		del_in(t_data **d, int **i)
{
	if ((*i)[4] <= (*i)[6])
		return ;
	ft_putstr_fd(tgetstr("sc", NULL), 0);
	ssupprchr(&((*d)->line), (*i)[4] - 1);
	if ((*d)->is_term)
	{
		erase_printline(d, i);
		ft_putstr_fd(((*d)->line + (*i)[6]), 0);
		ft_putstr_fd(tgetstr("rc", NULL), 0);
	}
	curs_left(d, i);
	(*i)[2]--;
	(*i)[4]--;
	(*i)[5] = 1;
}
