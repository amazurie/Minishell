/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 11:29:48 by amazurie          #+#    #+#             */
/*   Updated: 2017/06/13 16:11:46 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	do_setup(t_data **d, t_compl *c, char *word, int **i)
{
	t_arg	*args;
	int		j;

	if (!(c->args = list_arg(d, c, word, i)))
		return (0);
	c->line = ft_strdup((*d)->line);
	j = 0;
	if (word)
		j = ft_strlen(word);
	c->i4 = (*i)[4] - j;
	while (j-- > 0)
	{
		ssupprchr(&(c->line), c->i4);
		curs_left(d, i);
	}
	args = c->args;
	j = 0;
	while (args)
	{
		args->num = j;
		args = args->next;
		j++;
	}
	c->ac = j - 1;
	return (1);
}

void		insert_word(t_data **d, t_compl *c, char *word, int **i)
{
	if (c->ac != -1)
	{
		c->ac = 0;
		if (c->word)
			c->ac = ft_strlen(c->word);
		if (word)
			c->ac -= ft_strlen(word);
		while (c->ac-- > 0)
			curs_left(d, i);
		c->ac = 0;
		if (word)
			c->ac = ft_strlen(word);
		if (c->word)
			chr_in(d, (c->word + c->ac), i);
	}
	free_complargs(c->args);
	if (word)
		free(word);
	if (c->line)
		free(c->line);
	if (c->path_save)
		free(c->path_save);
}

int			completion(t_data **d, char **tmp, int **i)
{
	t_compl	c;
	char	*word;
	int		j;

	if ((*tmp)[0] != 9 || (*tmp)[1] || (*i)[6] > 0)
		return (0);
	c.is_term = (*d)->is_term;
	while ((*i)[4] < (*i)[2] && (*d)->line[(*i)[4]] != '"'
			&& (*d)->line[(*i)[4]] != '\'' && (*d)->line[(*i)[4]] != ' ')
	{
		curs_right(d, i);
		(*i)[4]++;
	}
	word = recover_wtocompl(d, i);
	c.word = word;
	c.path_save = NULL;
	if ((j = do_setup(d, &c, word, i)) == 0)
		free(word);
	if (j == 0)
		return (0);
	if ((j = compl_star(d, &c, i)) == 0)
		j = complet_arg(&c, tmp);
	c.ac = j;
	insert_word(d, &c, word, i);
	return (j);
}
