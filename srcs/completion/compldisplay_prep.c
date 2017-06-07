/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compldisplay_prep.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 11:29:36 by amazurie          #+#    #+#             */
/*   Updated: 2017/06/07 11:29:38 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_sline(t_compl *c, int col)
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
	while (i > col)
	{
		i -= col;
		j++;
	}
	return (j);
}

int	*get_size(t_compl *c)
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
