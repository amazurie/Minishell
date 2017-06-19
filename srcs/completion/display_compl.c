/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_compl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 11:29:53 by amazurie          #+#    #+#             */
/*   Updated: 2017/06/19 10:15:36 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_curspos(t_compl *c, char *word)
{
	struct winsize	w;
	int				j;

	ioctl(0, TIOCGWINSZ, &w);
	j = ft_strlen(get_prompt()) + ft_strlen(word) + c->i4;
	while (j > w.ws_col)
		j -= w.ws_col;
	if (j == w.ws_col)
		ft_putstr_fd(tgetstr("do", NULL), 0);
}

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

	ar = c->args;
	while (ar && ar->num != c->num_curr)
		ar = ar->next;
	i = get_sline(c, whcl[0]);
	if (ar)
		c->word = ar->elem;
	check_curspos(c, c->word);
	ft_putstr_fd(tgetstr("do", NULL), 0);
	ft_putstr_fd(tgetstr("up", NULL), 0);
	while (i-- > 0)
		ft_putstr_fd(tgetstr("up", NULL), 0);
	if (c->is_term)
	{
		display_prompt();
		ft_putnstr_fd(c->line, 0, c->i4);
		prep_compldisplay2(c, whcl);
	}
	else
		ft_putstr_fd("\n", 0);
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
		if (c->is_term == 0 && ar)
			ft_putchar_fd(' ', 0);
	}
}

void		display_compl(t_compl *c)
{
	t_arg	*ar;
	int		*whcl;

//	ft_putstr_fd(tgetstr("vi", NULL), 0);
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
	if (c->is_term == 0)
		ft_putchar_fd('\n', 0);
	display_prompt();
	ft_putnstr_fd(c->line, 0, c->i4);
	if (c->word)
		ft_putstr_fd(c->word, 0);
	check_curspos(c, c->word);
	ft_putstr_fd(tgetstr("ce", NULL), 0);
	ft_putstr_fd(tgetstr("ve", NULL), 0);
	free(whcl);
}
