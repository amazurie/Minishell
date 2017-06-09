/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 11:30:00 by amazurie          #+#    #+#             */
/*   Updated: 2017/06/07 14:19:24 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	browse_compl(t_data **d, t_compl *c, t_arg **list, char *word)
{
	t_arg	*tmplist;
	t_arg	*listtmp;
	char	**paths;
	int		j;

	j = 0;
	paths = ft_strsplit(get_elem((*d)->env, "PATH"), ':');
	tmplist = *list;
	while (paths && paths[j])
	{
		listtmp = list_content(c, paths[j++], word);
		if (listtmp && tmplist)
		{
			while (tmplist->next)
				tmplist = tmplist->next;
			tmplist->next = listtmp;
		}
		else if (listtmp && !tmplist)
		{
			*list = listtmp;
			tmplist = *list;
		}
	}
	free_tab(paths);
}

t_arg		*list_arg(t_data **d, t_compl *c, char *word, int **i)
{
	t_arg	*list;

	c->is_star = 0;
	c->is_dot = 0;
	if (word && word[0] && ft_strcmp(word, "*") == 0)
		c->is_star = 1;
	if (word && word[0] && ft_strcmp(word, "*") == 0)
		ft_bzero(word, ft_strlen(c->word));
	else if (word && word[0] && word[ft_strlen(word) - 1] == '*')
	{
		c->is_star = 3;
		word[ft_strlen(word) - 1] = 0;
	}
	c->is_slash = 0;
	if (!(list = list_content(c, word, word)))
		list = list_content(c, ".", word);
	else
	{
		if (c->is_slash == 0)
			chr_in(d, "/", i);
		return (list);
	}
	if (check_command(d, i) == 1 || c->is_star != 0)
		return (list);
	browse_compl(d, c, &list, word);
	return (list);
}
