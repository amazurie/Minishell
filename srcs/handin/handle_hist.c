/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 12:43:08 by amazurie          #+#    #+#             */
/*   Updated: 2017/05/24 17:18:11 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	del_lasts(t_hist **lst)
{
	t_hist	*h;
	t_hist	*tmp;

	h = *lst;
	while (h->next)
	{
		tmp = h;
		h = h->next;
	}
	free(h->hist);
	free(tmp->next);
	tmp->next = NULL;
}

void		add_hist(t_hist **lst, char *hist)
{
	t_hist	*h;
	t_hist	*tmp;
	int		i;

	h = *lst;
	if (h == NULL)
	{
		if ((*lst = (t_hist *)ft_memalloc(sizeof(t_hist))) == NULL)
			return ;
		(*lst)->num = 1;
		(*lst)->hist = ft_strdup(hist);
		(*lst)->next = NULL;
		return ;
	}
	i = 0;
	while (h->next && i++)
		h = h->next;
	if (i - 1 > MAX_HISTORY)
		del_lasts(lst);
	if ((tmp = (t_hist *)ft_memalloc(sizeof(t_hist))) == NULL)
		return ;
	tmp->num = (*lst)->num + 1;
	tmp->hist = ft_strdup(hist);
	tmp->next = *lst;
	*lst = tmp;
}

void		display_hist(t_hist *lst)
{
	t_hist	*h;

	h = lst;
	if (h == NULL)
		return ;
	while (h->next)
	{
		ft_putnbr(h->num);
		ft_putchar(' ');
		ft_putstr(h->hist);
		ft_putchar('\n');
		h = h->next;
	}
	ft_putnbr(h->num);
	ft_putchar(' ');
	ft_putstr(h->hist);
	ft_putchar('\n');
}

void		del_hist(t_hist *hist)
{
	t_hist	*h;

	if (hist == NULL)
		return ;
	while (hist->next)
	{
		h = hist;
		hist = hist->next;
		free(h->hist);
		free(h);
	}
	free(hist->hist);
	free(hist);
}
