/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand_in.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 12:16:34 by amazurie          #+#    #+#             */
/*   Updated: 2017/05/24 19:05:44 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	chr_in(t_data **d, char *tmp, int **i)
{
	ft_putstr_fd(tgetstr("sc", NULL), 0);
	erase_printline(d, i);
	if ((*i)[2] > 2040)
	{
		maxline(d, tmp, i);
		return ;
	}
	saddchr(&((*d)->line), tmp[0], (*i)[4]);
	ft_putstr_fd(((*d)->line + (*i)[6]), 0);
	ft_putstr_fd(tgetstr("rc", NULL), 0);
	curs_right(d, i);
	(*i)[2]++;
	(*i)[4]++;
	(*i)[5] = 1;
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

static int	gest_in(t_data **d, char *tmp, int **i)
{
	if (tmp[0] == 4 && !*(*d)->line)
		return (-1);
	else if (tmp[0] == 12)
	{
		ft_putstr_fd(tgetstr("cl", NULL), 0);
		if ((*i)[6] == 0)
			display_prompt((*d)->prompt);
		else
			ft_putstr_fd((*d)->prompt , 0);
		ft_putstr_fd(((*d)->line + (*i)[6]), 0);
	}
	else if (tmp[0] == 10)
		quote(d, i);
	else if (tmp[0] == 127 || tmp[0] == 8)
	{
		del_in(d, i);
		if (!(*d)->line[0])
			(*i)[5] = 0;
	}
	else if (ft_isprint(tmp[0]))
	{
		chr_in(d, &tmp[0], i);
		(*i)[5] = 1;
	}
	else
		gest_spekey(tmp, d, i);
	return (0);
}

void		inni(t_data **d, char *tmp, int **i)
{
	(*d)->i = *i;
	get_data(*d);
	read(0, tmp, 6);
	if (is_siginted(0) == 1)
	{
		ft_memset((*d)->line, 0, (*i)[2]);
		(*i)[2] = 0;
		(*i)[3] = -1;
		(*i)[4] = 0;
		(*i)[5] = 0;
		(*i)[6] = 0;
		free((*d)->prompt);
		(*d)->prompt = get_prompt();
	}
	if (gest_in(d, tmp, i) == -1)
		(*i)[0] = -1;
	ft_bzero(tmp, 6);
}

int			in(t_data **d, char *tmp)
{
	int		*i;
	int		j;

	is_siginted(1);
	if ((i = (int *)ft_memalloc(sizeof(int) * 7)) == NULL)
		return (print_error("allocation error") - 1);
	if (read(0, tmp, 0) == -1)
		return (-1);
	i[6] = 0;
	while (i[0] == 0)
		inni(d, tmp, &i);
	j = i[0];
	free(i);
	ft_putchar_fd('\n', 2);
	return (j);
}
