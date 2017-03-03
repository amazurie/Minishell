/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand_in.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 16:53:34 by amazurie          #+#    #+#             */
/*   Updated: 2017/03/03 17:15:10 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	leftright_key(char tmp, int **i, char **line)
{
	if (tmp == 67 || tmp == 68 || tmp == 126)
	{
		if ((*i)[4] > 0 && tmp == 68)
		{
			ft_putchar('\b');
			tmp = 0;
			(*i)[4]--;
		}
		else if ((*i)[4] < (*i)[2] && tmp == 67)
		{
			ft_putchar((*line)[(*i)[4]++]);
			tmp = 0;
		}
		return (1);
	}
	return (0);
}

int	endhome_key(char tmp, int **i, char **line)
{
	if (tmp == 72 || tmp == 70)
	{
		if (tmp == 72)
		{
			(*i)[1] = 0;
			while ((*i)[1]++ < (*i)[4])
				ft_putchar('\b');
			(*i)[4] = 0;
			return (1);
		}
		ft_putstr(((*line) + (*i)[4]));
		(*i)[4] = (*i)[2];
		return (1);
	}
	return (0);
}

int	del_key(char tmp, int **i, char **line)
{
	if (tmp == 51)
	{
		tmp = get_ch();
		if (tmp == 126 && (*i)[4] < (*i)[2])
		{
			ssupprchr(line, (*i)[4]);
			ft_putstr(((*line) + (*i)[4]));
			ft_putstr(" \b");
			(*i)[1] = (*i)[2];
			while (--(*i)[1] > (*i)[4])
				ft_putchar('\b');
			(*i)[2]--;
		}
		return (1);
	}
	return (endhome_key(tmp, i, line));
}

int	updown_key(char tmp, h_list *hist, int **i, char **line)
{
	if (tmp == 65)
	{
		if (((*i)[1] = disp_hist_next(hist, i, line)) != -1)
		{
			(*i)[2] = (*i)[1];
			(*i)[4] = (*i)[1];
		}
		else
			(*i)[4] = 0;
	}
	if (tmp == 66)
	{
		if (((*i)[1] = disp_hist_prec(hist, i, line)) != -1)
		{
			(*i)[2] = (*i)[1];
			(*i)[4] = (*i)[1];
		}
		else
			(*i)[4] = 0;
	}
	return (0);
}

int	gest_arrow(char tmp, h_list *hist, int **i, char **line)
{
	int	j;

	tmp = get_ch();
	tmp = get_ch();
	if (del_key(tmp, i, line))
		return (0);
	if (leftright_key(tmp, i, line))
		return (0);
	(*i)[1] = 0;
	while ((*i)[1]++ < (*i)[4])
		ft_putchar('\b');
	(*i)[1] = ft_strlen(*line);
	ft_memset(*line, ' ', (*i)[1]);
	ft_putstr(*line);
	ft_memset(*line, '\b', (*i)[1]);
	ft_putstr(*line);
	ft_memset(*line, 0, (*i)[1]);
	updown_key(tmp, hist, i, line);
	tmp = 0;
	return (0);
}
