/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_compl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 11:29:53 by amazurie          #+#    #+#             */
/*   Updated: 2017/06/20 14:57:20 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	disp_complarg(t_compl *c, t_arg **ar, int *whcl)
{
	ft_putstr_fd(tgetstr("do", NULL), 0);
	whcl[8] = whcl[7] * whcl[2];
	while (whcl[8]-- > 0)
		ft_putstr_fd(tgetstr("nd", NULL), 0);
	if ((*ar)->num == c->num_curr)
		ft_putstr_fd(tgetstr("mr", NULL), 0);
	if ((*ar)->color)
		ft_putstr_fd((*ar)->color, 0);
	ft_putstr_fd((*ar)->elem, 0);
	ft_putstr_fd(DEFAULT_COL, 0);
	ft_putstr_fd(tgetstr("me", NULL), 0);
	(*ar) = (*ar)->next;
	if (++whcl[6] == whcl[4] || whcl[6] == whcl[1])
	{
		whcl[7]++;
		while (whcl[6]-- > 0)
			ft_putstr_fd(tgetstr("up", NULL), 0);
		whcl[8] = whcl[5] + (whcl[4] - (whcl[5] + whcl[1]));
		while ((*ar) && whcl[8]-- > 0)
			(*ar) = (*ar)->next;
		whcl[6] = 0;
	}
	if (c->is_term == 0 && ar)
		ft_putchar_fd(' ', 0);
}

static void	disp_compl(t_compl *c, int **whcl)
{
	t_arg	*ar;

	ar = c->args;
	(*whcl)[8] = (*whcl)[5];
	while (ar && (*whcl)[8]-- > 0)
		ar = ar->next;
	while (ar)
		disp_complarg(c, &ar, *whcl);
}

void		display_compl(t_compl *c)
{
	int		*whcl;

	ft_putstr_fd(tgetstr("vi", NULL), 0);
	whcl = get_size(c);
	prep_compldisplay(c, whcl);
	whcl[6] = 0;
	whcl[7] = 0;
	disp_compl(c, &whcl);
	whcl[6] += get_sline(c, whcl[0]);
	while (whcl[6]-- > 0)
		ft_putstr_fd(tgetstr("up", NULL), 0);
	ft_putstr_fd(tgetstr("do", NULL), 0);
	ft_putstr_fd(tgetstr("up", NULL), 0);
	if (c->is_term == 0)
		ft_putchar_fd('\n', 0);
	display_prompt();
	ft_putnstr_fd(c->line, 0, c->i4);
	if (c->word)
		ft_putstr_fd(c->word, 0);
	compl_curspos(c, c->word);
	ft_putstr_fd(tgetstr("ce", NULL), 0);
	ft_putstr_fd(tgetstr("ve", NULL), 0);
	free(whcl);
}
