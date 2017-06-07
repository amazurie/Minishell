/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_compl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 11:29:53 by amazurie          #+#    #+#             */
/*   Updated: 2017/06/07 12:17:39 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	prep_compldisplay2(t_compl *c, int *whcl)
{
	int		i;

	if (c->word)
		ft_putstr_fd(c->word, 0);
	ft_putstr_fd((c->line + c->i4), 0);
	ft_putstr_fd(tgetstr("cd", NULL), 0);
	i = (whcl[4] > whcl[1]) ? whcl[1] : whcl[4];
	while (i-- > 0)
	{
		ft_putstr_fd(tgetstr("do", NULL), 0);
		ft_putstr_fd(tgetstr("dl", NULL), 0);
	}
	i = (whcl[4] > whcl[1]) ? whcl[1] : whcl[4];
	while (i-- > 0)
		ft_putstr_fd(tgetstr("up", NULL), 0);
}

static void	prep_compldisplay(t_compl *c, int *whcl)
{
	t_arg	*ar;
	int		i;

	ft_putstr_fd((c->line + c->i4), 0);
	i = get_sline(c, whcl[0]);
	ft_putstr_fd(tgetstr("do", NULL), 0);
	ft_putstr_fd(tgetstr("up", NULL), 0);
	while (i-- > 0)
		ft_putstr_fd(tgetstr("up", NULL), 0);
	display_prompt();
	ft_putnstr_fd(c->line, 0, c->i4);
	ar = c->args;
	while (ar && ar->num != c->num_curr)
		ar = ar->next;
	if (ar)
		c->word = ar->elem;
	prep_compldisplay2(c, whcl);
}

static void	disp_complarg(t_compl *c, t_arg *ar, int *whcl)
{
	while (ar)
	{
		ft_putstr_fd(tgetstr("do", NULL), 0);
		whcl[8] = whcl[7] * whcl[2];
		while (whcl[8]-- > 0)
			ft_putstr_fd(tgetstr("nd", NULL), 0);
		if (ar->num == c->num_curr)
			ft_putstr_fd(tgetstr("mr", NULL), 0);
		if (ar->color)
			ft_putstr_fd(ar->color, 0);
		ft_putstr_fd(ar->elem, 0);
		ft_putstr_fd(DEFAULT_COL, 0);
		ft_putstr_fd(tgetstr("me", NULL), 0);
		ar = ar->next;
		if (++whcl[6] == whcl[4] || whcl[6] == whcl[1])
		{
			whcl[7]++;
			while (whcl[6]-- > 0)
				ft_putstr_fd(tgetstr("up", NULL), 0);
			whcl[8] = whcl[5] + (whcl[4] - (whcl[5] + whcl[1]));
			while (ar && whcl[8]-- > 0)
				ar = ar->next;
			whcl[6] = 0;
		}
	}
}

void		display_compl(t_compl *c)
{
	t_arg	*ar;
	int		*whcl;

	ft_putstr_fd(tgetstr("vi", NULL), 0);
	whcl = get_size(c);
	prep_compldisplay(c, whcl);
	whcl[6] = 0;
	whcl[7] = 0;
	ar = c->args;
	whcl[8] = whcl[5];
	while (ar && whcl[8]-- > 0)
		ar = ar->next;
	disp_complarg(c, ar, whcl);
	whcl[6] += get_sline(c, whcl[0]);
	while (whcl[6]-- > 0)
		ft_putstr_fd(tgetstr("up", NULL), 0);
	ft_putstr_fd(tgetstr("do", NULL), 0);
	ft_putstr_fd(tgetstr("up", NULL), 0);
	display_prompt();
	ft_putnstr_fd(c->line, 0, c->i4);
	if (c->word)
		ft_putstr_fd(c->word, 0);
	ft_putstr_fd(tgetstr("ce", NULL), 0);
	ft_putstr_fd(tgetstr("ve", NULL), 0);
	free(whcl);
}
