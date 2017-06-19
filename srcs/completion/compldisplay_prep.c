/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compldisplay_prep.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 11:29:36 by amazurie          #+#    #+#             */
/*   Updated: 2017/06/19 10:30:28 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			get_sline(t_compl *c, int col)
{
	char	*prompt;
	int		i;
	int		j;

	j = 0;
	prompt = get_prompt();
	i = ft_strlen(c->line) + ft_strlen(prompt);
	free(prompt);
	if (c->word)
		i += ft_strlen(c->word);
	while (i >= col)
	{
		i -= col;
		j++;
	}
	return (j);
}

int			*get_size(t_compl *c)
{
	struct winsize	w;
	int				*whcl;

	if (!(whcl = (int *)ft_memalloc(sizeof(int) * 9)))
		return (0);
	ioctl(0, TIOCGWINSZ, &w);
	whcl[0] = w.ws_col;
	whcl[1] = w.ws_row - get_sline(c, whcl[0]) - 1;
	whcl[3] = nbrline(c->args, whcl[0], &whcl[2]);
	whcl[4] = nbr_col(c->args, &whcl[3]);
	whcl[5] = check_winsize(c, whcl);
	c->min_line = whcl[5];
	return (whcl);
}

void		compl_curspos(t_compl *c, char *word)
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

void		prep_compldisplay(t_compl *c, int *whcl)
{
	t_arg	*ar;
	int		i;

	ar = c->args;
	while (ar && ar->num != c->num_curr)
		ar = ar->next;
	i = get_sline(c, whcl[0]);
	if (ar)
		c->word = ar->elem;
	compl_curspos(c, c->word);
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
