/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand_in.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 16:53:34 by amazurie          #+#    #+#             */
/*   Updated: 2017/04/12 12:32:38 by amazurie         ###   ########.fr       */
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
			ft_putchar_fd('\b', 0);
			(*i)[4]--;
		}
		else if ((*i)[4] < (*i)[2] && (tmp[2] == 67
					|| tmp[0] == 6))
			ft_putchar_fd((*line)[(*i)[4]++], 0);
		return (1);
	}
	return (0);
}

int	updown_key(t_data **d, char *tmp, int **i)
{
	if (tmp[2] == 65 || tmp[2] == 53 || tmp[0] == 16)
	{
		if (((*i)[1] = disp_hist_next(d, i)) != -1)
		{
			(*i)[2] = (*i)[1];
			(*i)[4] = (*i)[1];
		}
		else
			return (0);
	}
	else
	{
		if (((*i)[1] = disp_hist_prec(d, i)) != -1)
		{
			(*i)[2] = (*i)[1];
			(*i)[4] = (*i)[1];
		}
		else
			return (-1);
	}
	return (1);
}

int	updown_gest(char *tmp, t_data **d, int **i)
{
	int j;

	if ((*i)[5] == 1)
		ft_strcpy(((*d)->buffline), (*d)->line);
	erase_printline(d, i);
	if ((j = updown_key(d, tmp, i)) <= 0)
	{
		if (j == -1)
		{
			ft_memset((*d)->line, 0, (*i)[2]);
			ft_strcpy((*d)->line, (*d)->buffline);
			ft_putstr_fd((*d)->line, 0);
			(*i)[2] = ft_strlen((*d)->line);
			(*i)[4] = (*i)[2];
			ft_bzero((*d)->buffline, ft_strlen((*d)->buffline));
			(*i)[5] = 1;
		}
	}
	return (0);
}

int	gest_spekey(char *tmp, t_data **d, int **i)
{
	if (del_key(tmp, i, d) || leftright_key(tmp, i, &((*d)->line))
			|| del_line(&((*d)->line), tmp, i))
		return (0);
	if (tmp[2] != 65 && tmp[2] != 53 && tmp[2] != 66
			&& tmp[2] != 54 && tmp[0] != 16 && tmp[0] != 14)
		return (0);
	updown_gest(tmp, d, i);
	return (0);
}
