/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 12:43:08 by amazurie          #+#    #+#             */
/*   Updated: 2017/02/27 14:01:00 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_lasts(h_list **lst, int nbr)
{
	h_list	*h;
	h_list	*tmp;
	int		i;

	h = *lst;
	while (h->next)
	{
		h = h->next;
		i++;
	}
	i -= nbr;
	if (i < 0)
		return ;
	h = *lst;
	while (h->next && i--)
	{
		h->num -= nbr;
		h = h->next;
	}
	while (i > 0 && h->next)
	{
		tmp = h->next;
		free(h->hist);
		free(h);
		h = tmp;
	}
	free(h->hist);
	free(h);
}

void	add_hist(h_list **lst, char *hist)
{
	h_list	*h;
	int		i;

	h = *lst;
	if (h == NULL)
	{
		h = (h_list *)ft_memalloc(sizeof(h_list));
		h->num = 1;
		h->hist = ft_strdup(hist);
		h->next = NULL;
		*lst = h;
		return ;
	}
	while (h->next)
	{
		h = h->next;
		i++;
	}
//	if (i > MAX_HISTORY)
//		del_lasts(lst, i - MAX_HISTORY);
	h = (h_list *)ft_memalloc(sizeof(h_list));
	h = h->next;
	h->num = h->next->num + 1;
	h->hist = ft_strdup(hist);
	h->next = *lst;
	*lst = h;
}

void	display_hist(h_list **lst)
{
	h_list	*h;

	h = *lst;
	if (h == NULL)
		return ;
	while (h->next)
	{
		ft_putnbr(h->num);
		ft_putstr(h->hist);
		ft_putchar('\n');
		h = h->next;
	}
	ft_putnbr(h->num);
	ft_putstr(h->hist);
	ft_putchar('\n');
}
