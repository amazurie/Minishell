/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:28:50 by amazurie          #+#    #+#             */
/*   Updated: 2017/02/27 17:34:58 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		disp_hist_next(h_list *lst, int *histnum, char **line)
{
	h_list *h;

	h = lst;
	if (!h)
		return (-1);
	if (*histnum == -1 || *histnum == 0)
	{
		ft_putstr(h->hist);
		*line = ft_strdup(h->hist);
		*histnum = h->num;
		return (ft_strlen(h->hist));
	}
	while (h->next && h->num != *histnum)
		h = h->next;
	if (h->next && h->num == *histnum)
	{
		h = h->next;
		ft_putstr(h->hist);
		*line = ft_strdup(h->hist);
		*histnum = h->num;
		return (ft_strlen(h->hist));
	}
	return (-1);
}

int		disp_hist_prec(h_list *lst, int *histnum, char **line)
{
	h_list *h;
	h_list *tmp;

	h = lst;
	tmp = NULL;
	if (!h)
		return (-1);
	if (*histnum == -1 || *histnum == 0)
		return (-1);
	while (h->next && h->num != *histnum)
	{
		tmp = h;
		h = h->next;
	}
	if (tmp != NULL && h->num == *histnum)
	{
		ft_putstr(tmp->hist);
		*line = ft_strdup(tmp->hist);
		*histnum = tmp->num;
		return (ft_strlen(tmp->hist));
	}
	return (-1);
}
