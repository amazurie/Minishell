/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compl_star.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 11:29:29 by amazurie          #+#    #+#             */
/*   Updated: 2017/06/07 12:18:59 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	prep_complstar2(t_data **d, t_compl *c, int **i)
{
	if (c->word)
		curs_right(d, i);
	if (c->path_save[ft_strlen(c->path_save) - 1] == '/')
		c->path_save[ft_strlen(c->path_save) - 1] = 0;
	if (!c->is_slash)
	{
		ssupprchr(&((*d)->line), (*i)[4] - 1);
		curs_left(d, i);
		(*i)[4]--;
		(*i)[2]--;
	}
}

static int	compl_star2(t_data **d, t_compl *c, int **i)
{
	t_arg	*ar;
	char	*tmp;
	char	*tmp2;

	prep_complstar2(d, c, i);
	ar = c->args;
	tmp2 = ft_strjoin("/", ar->elem);
	tmp = ft_strjoin(tmp2, " ");
	free(tmp2);
	while (ar && (ar = ar->next))
	{
		tmp2 = ft_strjoin(tmp, c->path_save);
		free(tmp);
		tmp = ft_strjoin(tmp2, "/");
		free(tmp2);
		tmp2 = ft_strjoin(tmp, ar->elem);
		free(tmp);
		tmp = ft_strjoin(tmp2, " ");
		free(tmp2);
	}
	chr_in(d, tmp, i);
	free(tmp);
	return (1);
}

static void	prep_complstar(t_data **d, t_compl *c, int **i)
{
	ssupprchr(&((*d)->line), (*i)[4] - 1);
	if (c->is_star == 1)
		curs_left(d, i);
	(*i)[4]--;
	(*i)[2]--;
	if (c->word && c->is_star > 1)
	{
		while (c->word && c->word[0]
				&& c->word[ft_strlen(c->word) - 1] == (*d)->line[(*i)[4] - 1])
		{
			ssupprchr(&((*d)->line), (*i)[4] - 1);
			ssupprchr(&c->word, ft_strlen(c->word) - 1);
			curs_left(d, i);
			(*i)[4]--;
			(*i)[2]--;
		}
		if ((*d)->line[(*i)[4] - 1] == '/')
		{
			ssupprchr(&((*d)->line), (*i)[4] - 1);
			(*i)[4]--;
			(*i)[2]--;
		}
	}
}

int			compl_star(t_data **d, t_compl *c, int **i)
{
	t_arg	*ar;
	char	*tmp;
	char	*tmp2;

	if (c->is_star == 0)
		return (0);
	prep_complstar(d, c, i);
	if (c->is_star == 2 || (c->is_star == 3 && c->path_save))
		return (compl_star2(d, c, i));
	ar = c->args;
	tmp = ft_strjoin(ar->elem, " ");
	while (ar && (ar = ar->next))
	{
		tmp2 = ft_strjoin(tmp, ar->elem);
		free(tmp);
		tmp = ft_strjoin(tmp2, " ");
		free(tmp2);
	}
	chr_in(d, tmp, i);
	free(tmp);
	return (1);
}
