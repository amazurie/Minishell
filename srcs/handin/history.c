/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:28:50 by amazurie          #+#    #+#             */
/*   Updated: 2017/06/13 15:59:48 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	disp_hist(t_data **d, t_hist *h, int **i)
{
	if ((*d)->is_term == 1)
		erase_printline(d, i);
	ft_bzero(((*d)->line + (*i)[6]), (*i)[2] - (*i)[6]);
	(*i)[2] = (*i)[6];
	(*i)[4] = (*i)[2];
	chr_in(d, h->hist, i);
	(*i)[3] = h->num;
	(*i)[5] = 0;
	return (ft_strlen((*d)->line));
}

int			disp_hist_next(t_data **d, int **i)
{
	t_hist	*h;

	(*i)[5] = 0;
	h = (*d)->hist;
	if (!h)
		return (-1);
	while (h->next && ((h->num >= (*i)[3] && (*i)[3] != -1)
				|| (((*i)[3] == -1 || h->num < (*i)[3])
					&& ft_strncmp(h->hist, (*d)->buffline,
						ft_strlen((*d)->buffline)))))
		h = h->next;
	if (!ft_strncmp(h->hist, (*d)->buffline,
				ft_strlen((*d)->buffline)))
		return (disp_hist(d, h, i));
	return (-1);
}

int			disp_hist_prec(t_data **d, int **i)
{
	t_hist	*h;
	t_hist	*tmp;

	(*i)[5] = 0;
	h = (*d)->hist;
	tmp = NULL;
	if (!h || (*i)[3] == -1)
		return (-1);
	while (h->next && h->num > (*i)[3])
	{
		if (!ft_strncmp(h->hist, (*d)->buffline, ft_strlen((*d)->buffline)))
			tmp = h;
		h = h->next;
	}
	if (tmp)
		return (disp_hist(d, tmp, i));
	(*i)[3] = -1;
	return (-1);
}
