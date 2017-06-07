/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_argcompl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 12:10:47 by amazurie          #+#    #+#             */
/*   Updated: 2017/06/07 14:32:18 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_compllist(t_arg **list, t_arg *listtmp)
{
	if (listtmp)
	{
		if (listtmp->next)
			free(listtmp->next);
		listtmp->next = NULL;
		return (1);
	}
	else if (!listtmp)
		free(*list);
	return (0);
}

static int	r_complcont(t_arg **list, DIR *dirp, t_compl *c, char *pathcol)
{
	struct dirent	*dirc;
	t_arg			*tmplist;
	t_arg			*listtmp;
	int				i;

	tmplist = *list;
	listtmp = NULL;
	i = 0;
	while ((dirc = readdir(dirp)))
	{
		if ((!c->word || !ft_strncmp(c->word, dirc->d_name, ft_strlen(c->word))
				|| !c->word[0]) && (dirc->d_name[0] != '.' || (c->is_dot == 1
					&& dirc->d_name[1] && dirc->d_name[1] != '.')))
		{
			tmplist->num = i++;
			tmplist->elem = ft_strdup(dirc->d_name);
			compl_addcolor(&tmplist, pathcol, dirc->d_name);
			if (!(tmplist->next = (t_arg *)ft_memalloc(sizeof(t_arg))))
				return (0);
			listtmp = tmplist;
			tmplist = tmplist->next;
		}
	}
	return (check_compllist(list, listtmp));
}

static void	compl_cmp(t_compl *c, char *path, char **word, char **pathcol)
{
	if (ft_strcmp(path, *word) == 0)
	{
		if ((*word)[0] == '.' && (!(*word)[1]
				|| ((*word)[1] != '.' && !(*word)[2])))
			c->is_dot = 1;
		*pathcol = ft_strdup(path);
		if (c->is_dot || (*word)[ft_strlen(*word) - 1] == '/')
			c->is_slash = 1;
		if (!c->is_dot)
			ft_bzero(*word, ft_strlen(*word));
	}
	else if (ft_strcmp(path, ".") == 0)
		*pathcol = ft_strdup(path);
	if ((*word)[0] == '.')
		c->is_dot = 1;
}

t_arg		*list_content(t_compl *c, char *path, char *word)
{
	DIR		*dirp;
	t_arg	*list;
	char	*pathcol;

	if (!path || !(dirp = opendir(path)))
		return (NULL);
	pathcol = NULL;
	compl_cmp(c, path, &word, &pathcol);
	if (!(list = (t_arg *)ft_memalloc(sizeof(t_arg))))
	{
		closedir(dirp);
		return (NULL);
	}
	if (r_complcont(&list, dirp, c, pathcol) == 0)
		list = NULL;
	closedir(dirp);
	if (pathcol)
		free(pathcol);
	return (list);
}
