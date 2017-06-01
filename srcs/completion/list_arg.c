#include "minishell.h"

static int	check_compllist(t_arg **list, t_arg *listtmp)
{
	if (!listtmp)
	{
		free(*list);
		return (0);
	}
	else if (listtmp)
	{
		if (listtmp->next)
			free (listtmp->next);
		listtmp->next = NULL;
	}
	return (1);
}

static int	read_complcont(t_arg **list, DIR *dirp, t_compl *c, char *pathcolor)
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
			compl_addcolor(&tmplist, pathcolor, dirc->d_name);
			if (!(tmplist->next = (t_arg *)ft_memalloc(sizeof(t_arg))))
				return (0);
			listtmp = tmplist;
			tmplist = tmplist->next;
		}
	}
	return (check_compllist(list, listtmp));
}

static t_arg	*list_content(t_compl *c, char *path, char *word)
{
	DIR		*dirp;
	t_arg	*list;
	char	*pathcolor;

	if (!path || !(dirp = opendir(path)))
		return (NULL);
	pathcolor = NULL;
	if (ft_strcmp(path, word) == 0)
	{
		if (word[0] == '.')
			c->is_dot = 1;
		pathcolor = ft_strdup(path);
		if (c->is_dot || word[ft_strlen(word) - 1] == '/')
			c->is_slash = 1;
		if (!c->is_dot)
			ft_bzero(word, ft_strlen(word));
	}
	else if (ft_strcmp(path, ".") == 0)
		pathcolor = ft_strdup(path);
	if (word[0] == '.')
		c->is_dot = 1;
	if (!(list = (t_arg *)ft_memalloc(sizeof(t_arg))))
	{
		closedir(dirp);
		return (NULL);
	}
	if (read_complcont(&list, dirp, c, pathcolor) == 0)
		list = NULL;
	closedir(dirp);
	if (pathcolor)
		free(pathcolor);
	return (list);
}

static void	browse_complpath(t_data **d, t_compl *c, t_arg **list, char *word)
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

t_arg	*list_arg(t_data **d, t_compl *c, int **i, char *word)
{
	t_arg	*list;

	c->is_star = 0;
	c->is_dot = 0;
	if (ft_strcmp(word,  "*") == 0)
		c->is_star = 1;
	if (ft_strcmp(word,  "*") == 0)
		ft_bzero(word, ft_strlen(word));
	c->is_slash = 0;
	if (!(list = list_content(c, word, word)))
		list = list_content(c, ".", word);
	else
	{
		if (c->is_slash == 0)
			chr_in(d, "/", i);
		return (list);
	}
	if (check_command(d, i) == 1 || c->is_star == 1)
		return (list);
	browse_complpath(d, c, &list, word);
	return (list);
}
