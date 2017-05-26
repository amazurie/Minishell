/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:28:50 by amazurie          #+#    #+#             */
/*   Updated: 2017/05/24 16:39:51 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		disp_hist_next(t_data **d, int **i)
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
	{
		erase_printline(d, i);
		ft_bzero(((*d)->line + (*i)[6]), (*i)[2] - (*i)[6]);
		ft_putstr_fd(h->hist, 0);
		ft_strcpy(((*d)->line + (*i)[6]), h->hist);
		(*i)[3] = h->num;
		return (ft_strlen((*d)->line));
	}
	return (-1);
}

int		disp_hist_prec(t_data **d, int **i)
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
	{
		erase_printline(d, i);
		ft_bzero(((*d)->line + (*i)[6]), (*i)[2] - (*i)[6]);
		ft_putstr_fd(tmp->hist, 0);
		ft_strcpy(((*d)->line + (*i)[6]), tmp->hist);
		(*i)[3] = tmp->num;
		return (ft_strlen((*d)->line));
	}
	(*i)[3] = -1;
	return (-1);
}
