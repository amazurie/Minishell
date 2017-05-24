/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand_in.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 16:53:34 by amazurie          #+#    #+#             */
/*   Updated: 2017/05/24 16:18:20 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	line_updown(t_data **d, char *tmp, int **i)
{
	struct winsize	w;
	int				j;

	if (tmp[0] != 27 || tmp[1] != 27 || tmp[2] != 91
			|| (tmp[3] != 65 && tmp[3] != 66))
		return (0);
	ioctl(0, TIOCGWINSZ, &w);
	j = 0;
	if (tmp[3] == 65)
	{
		while (j < w.ws_col && (*i)[4] > (*i)[6])
		{
			curs_left(d, i);
			j++;
			(*i)[4]--;
		}
		return (1);
	}
	while (j < w.ws_col && (*i)[4] < (*i)[2])
	{
		curs_right(d, i);
		j++;
		(*i)[4]++;
	}
	return (1);
}

static void	word_moveleft(t_data **d, int **i)
{
	if ((*d)->line[(*i)[4]] && (*d)->line[(*i)[4]] != 32)
	{
		curs_left(d, i);
		(*i)[4]--;
	}
	while (((*d)->line[(*i)[4]] && (*d)->line[(*i)[4]] == 32)
			|| (*i)[4] == (*i)[2])
	{
		curs_left(d, i);
		(*i)[4]--;
	}
	while ((*d)->line[(*i)[4]] && (*d)->line[(*i)[4]] != 32)
	{
		curs_left(d, i);
		(*i)[4]--;
	}
	curs_right(d, i);
	(*i)[4]++;
}

static int		word_move(t_data **d, char *tmp, int **i)
{
	if (tmp[0] != 27 || tmp[1] != 27 || tmp[2] != 91
			|| (tmp[3] != 67 && tmp[3] != 68))
		return (0);
	if (tmp[3] == 67)
	{
		while ((*d)->line[(*i)[4]] && (*d)->line[(*i)[4]] != 32)
		{
			curs_right(d, i);
			(*i)[4]++;
		}
		while ((*d)->line[(*i)[4]] && (*d)->line[(*i)[4]] == 32)
		{
			curs_right(d, i);
			(*i)[4]++;
		}
		return (1);
	}
	word_moveleft(d, i);
	return (1);
}

int		gest_spekey(char *tmp, t_data **d, int **i)
{
	if (del_key(tmp, i, d) || leftright_key(d, tmp, i)
			|| del_line(&((*d)->line), tmp, i) || word_move(d, tmp, i)
			|| line_updown(d, tmp, i))
		return (0);
	if (tmp[2] != 65 && tmp[2] != 53 && tmp[2] != 66
			&& tmp[2] != 54 && tmp[0] != 16 && tmp[0] != 14)
		return (0);
	updown_gest(tmp, d, i);
	return (0);
}
