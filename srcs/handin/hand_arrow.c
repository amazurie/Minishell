/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand_arrow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 16:17:54 by amazurie          #+#    #+#             */
/*   Updated: 2017/05/24 16:17:55 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		leftright_key(t_data **d, char *tmp, int **i)
{
	if ((tmp[0] == 27 && tmp[1] == 91 && (tmp[2] == 67 || tmp[2] == 68)
			&& !tmp[3]) || (tmp[0] == 6 && !tmp[1])
			|| (tmp[0] == 2 && !tmp[1]))
	{
		if ((*i)[4] > (*i)[6] && (tmp[2] == 68 || tmp[0] == 2))
		{
			curs_left(d, i);
			(*i)[4]--;
			(*i)[5] = 1;
		}
		else if ((*i)[4] < (*i)[2] && (tmp[2] == 67
					|| tmp[0] == 6))
		{
			curs_right(d, i);
			(*i)[4]++;
		}
		return (1);
	}
	return (0);
}

static int	updown_key(t_data **d, char *tmp, int **i)
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

int		updown_gest(char *tmp, t_data **d, int **i)
{
	int j;

	ft_putstr_fd(tgetstr("sc", NULL), 0);
	if ((*i)[5] == 1)
		ft_strcpy((*d)->buffline, ((*d)->line + (*i)[6]));
	if ((j = updown_key(d, tmp, i)) <= 0)
	{
		if (j == -1)
		{
			erase_printline(d, i);
			ft_strcpy(((*d)->line + (*i)[6]), (*d)->buffline);
			ft_putstr_fd(((*d)->line + (*i)[6]), 0);
			(*i)[2] = ft_strlen((*d)->line);
			(*i)[4] = (*i)[2];
			ft_bzero((*d)->buffline, ft_strlen((*d)->buffline));
			(*i)[5] = 1;
		}
		else
			ft_putstr_fd(tgetstr("rc", NULL), 0);
	}
	return (0);
}
