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

static int	compl_cmp(t_compl *c, char *path, char **word, char *path2)
{
	int	i;
	int	j;

	j = 0;
	if (word && word[0] && ft_strcmp(path, *word) == 0 && (j = 1) > 0)
	{
		if ((*word)[0] == '.' && (!(*word)[1] || ((*word)[1] != '.'
					&& (*word)[1] != '/' && !(*word)[2])))
			c->is_dot = 1;
		if (c->is_dot || (*word)[ft_strlen(*word) - 1] == '/')
			c->is_slash = 1;
		c->is_star = (c->is_star == 3) ? 2 : 0;
		c->path_save = ft_strdup(path2);
		i = ft_strlen(*word) - 1;
		while (i > 0 && (*word)[i] != '/' && (size_t)i > ft_strlen(path2) - 1)
			i--;
		if (!c->is_dot && (i <= 0 || (size_t)i == ft_strlen(*word) - 1))
			ft_bzero(*word, ft_strlen(*word));
		else if (!c->is_dot && ++i > 0 && (c->is_slash = 1) > 0)
		{
			ft_memmove(*word, (*word + i), ft_strlen((*word + i)));
			ft_bzero((*word + ft_strlen((*word + i))), ft_strlen((*word + i)));
		}
	}
	else if (ft_strcmp(path, ".") == 0)
		j = 1;
	return (j);
}

DIR			*check_open(char *firstpath, char **path)
{
	DIR		*dirp;
	int		i;

	if (!firstpath || !firstpath[0])
		return (NULL);
	if (!(*path = ft_strdup(firstpath)))
		return (NULL);
	if (!(dirp = opendir(*path)))
	{
		i = ft_strlen(*path) - 1;
		while (i > 0 && (*path)[i] && (*path)[i] != '/')
			i--;
		ft_bzero((*path + i), ft_strlen(*path + i));
		if (!*path || !(dirp = opendir(*path)))
		{
			if (*path)
				free(*path);
			return (NULL);
		}
	}
	return (dirp);
}

t_arg		*list_content(t_compl *c, char *firstpath, char *word)
{
	DIR		*dirp;
	t_arg	*list;
	char	*pathcol;
	char	*path;

	pathcol = NULL;
	if (!(dirp = check_open(firstpath, &path)))
		return (NULL);
	if (compl_cmp(c, firstpath, &word, path))
		pathcol = ft_strdup(path);
	if (word && word[0] == '.')
		c->is_dot = 1;
	if (!(list = (t_arg *)ft_memalloc(sizeof(t_arg))))
	{
		closedir(dirp);
		free(path);
		return (NULL);
	}
	if (r_complcont(&list, dirp, c, pathcol) == 0)
		list = NULL;
	closedir(dirp);
	if (pathcol)
		free(pathcol);
	free(path);
	return (list);
}
