/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand_in.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 16:53:34 by amazurie          #+#    #+#             */
/*   Updated: 2017/03/08 17:41:16 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	leftright_key(char *tmp, int **i, char **line)
{
	if (tmp[2] == 67 || tmp[2] == 68 || tmp[2] == 126
			|| tmp[0] == 6 || tmp[0] == 2)
	{
		if ((*i)[4] > 0 && (tmp[2] == 68 || tmp[0] == 2))
		{
			ft_putchar('\b');
			(*i)[4]--;
		}
		else if ((*i)[4] < (*i)[2] && (tmp[2] == 67
					|| tmp[0] == 6))
			ft_putchar((*line)[(*i)[4]++]);
		return (1);
	}
	return (0);
}

int	endhome_key(char *tmp, int **i, char **line)
{
	if (tmp[2] == 72 || tmp[2] == 70 || tmp[0] == 1
			|| tmp[0] == 5)
	{
		if (tmp[2] == 72 || tmp[0] == 1)
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

int	del_key(char *tmp, int **i, char **line)
{
	if (tmp[2] == 51 || tmp[0] == 4)
	{
		if ((tmp[0] == 4 || tmp[3] == 126) && (*i)[4] < (*i)[2])
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

int	updown_key(char *tmp, h_list *hist, int **i, char **line)
{
	if (tmp[2] == 65 || tmp[2] == 53 || tmp[0] == 16)
	{
		if (((*i)[1] = disp_hist_next(hist, i, line)) != -1)
		{
			(*i)[2] = (*i)[1];
			(*i)[4] = (*i)[1];
		}
		else
			return (0);
	}
	else
	{
		if (((*i)[1] = disp_hist_prec(hist, i, line)) != -1)
		{
			(*i)[2] = (*i)[1];
			(*i)[4] = (*i)[1];
		}
		else
			return (0);
	}
	return (1);
}

int	gest_spekey(char *tmp, h_list *hist, int **i, char **line)
{
	if (del_key(tmp, i, line) || leftright_key(tmp, i, line)
			|| del_line(line, tmp, i))
		return (0);
	if (tmp[2] != 65 && tmp[2] != 53 && tmp[2] != 66
			&& tmp[2] != 54 && tmp[0] != 16 && tmp[0] != 14)
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
	if (updown_key(tmp, hist, i, line) == 0)
	{
		(*i)[2] = 0;
		(*i)[4] = 0;
	}
	tmp = 0;
	return (0);
}
