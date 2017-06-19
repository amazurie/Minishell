/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_in.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 12:30:47 by amazurie          #+#    #+#             */
/*   Updated: 2017/06/13 16:03:34 by amazurie         ###   ########.fr       */
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

void		chr_in(t_data **d, char *tmp, int **i)
{
	int	j;
	int	i4;

	(*i)[5] = 1;
	if ((*d)->is_term == 1)
		erase_printline(d, i);
	j = -1;
	while (tmp[++j])
	{
		if ((*i)[2] > LIMIT_LINE - 1)
		{
			maxline(d, tmp, i);
			return ;
		}
		saddchr(&((*d)->line), tmp[j], (*i)[4] + j);
		(*i)[2]++;
		if ((*d)->is_term == 0)
			ft_putchar_fd(tmp[j], 0);
	}
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
