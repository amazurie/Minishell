/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:28:50 by amazurie          #+#    #+#             */
/*   Updated: 2017/02/28 14:20:47 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		disp_hist_next(h_list *lst, int **i, char **line)
{
	h_list *h;

	h = lst;
	if (!h)
		return (-1);
	if ((*i)[3] == -1)
	{
		ft_putstr(h->hist);
		*line = ft_strdup(h->hist);
		(*i)[3] = h->num;
		return (ft_strlen(h->hist));
	}
	while (h->next && h->num != (*i)[3])
		h = h->next;
	if (h->next && h->num == (*i)[3])
	{
		h = h->next;
		ft_putstr(h->hist);
		*line = ft_strdup(h->hist);
		(*i)[3] = h->num;
		return (ft_strlen(h->hist));
	}
	if (!h->next)
		(*i)[3] = 0;
	return (-1);
}

int		disp_hist_prec(h_list *lst, int **i, char **line)
{
	h_list *h;
	h_list *tmp;

	h = lst;
	tmp = NULL;
	if (!h)
		return (-1);
	if ((*i)[3] == -1)
		return (-1);
	while (h->next && h->num != (*i)[3])
	{
		tmp = h;
		h = h->next;
	}
	if ((*i)[3] == 0 && h != NULL)
		tmp = h;
	if (tmp != NULL && (h->num == (*i)[3] || (*i)[3] == 0))
	{
		ft_putstr(tmp->hist);
		*line = ft_strdup(tmp->hist);
		(*i)[3] = tmp->num;
		return (ft_strlen(tmp->hist));
	}
	return (-1);
}
