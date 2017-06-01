#include "minishell.h"

t_arg	*list_content(t_compl *c, char *path, char *word)
{
	struct dirent	*dirc;
	DIR				*dirp;
	t_arg			*list;
	t_arg			*tmplist;
	t_arg			*listtmp;
	int				i;

	if (!path || !(dirp = opendir(path)))
		return (NULL);
	if (ft_strcmp(path, word) == 0)
	{
		if (word[ft_strlen(word) - 1] == '/')
			c->is_slash = 1;
		ft_bzero(word, ft_strlen(word));
	}
	if (!(list = (t_arg *)ft_memalloc(sizeof(t_arg))))
	{
		closedir(dirp);
		return (NULL);
	}
	tmplist = list;
	listtmp = NULL;
	i = 0;
	while ((dirc = readdir(dirp)))
	{
		if ((!word || ft_strncmp(word, dirc->d_name, ft_strlen(word)) == 0
				|| !word[0]) && dirc->d_name[0] != '.')
		{
			tmplist->num = i++;
			tmplist->elem = ft_strdup(dirc->d_name);
			if (!(tmplist->next = (t_arg *)ft_memalloc(sizeof(t_arg))))
			{
				closedir(dirp);
				return (NULL);
			}
			listtmp = tmplist;
			tmplist = tmplist->next;
		}
	}
	if (!listtmp)
	{
		free(list);
		closedir(dirp);
		return (NULL);
	}
	else if (listtmp)
	{
		if (listtmp->next)
			free (listtmp->next);
		listtmp->next = NULL;
	}
	closedir(dirp);
	return (list);
}

t_arg	*list_arg(t_data **d, t_compl *c, int **i, char *word)
{
	t_arg	*list;
	t_arg	*tmplist;
	t_arg	*listtmp;
	char	**paths;
	int		j;

	j = 0;
	c->is_slash = 0;
	if (!(list = list_content(c, word, word)))
		list = list_content(c, ".", word);
	else
	{
		if (c->is_slash == 0)
			chr_in(d, "/", i);
		return (list);
	}
	if (check_command(d, i) == 1)
		return (list);
	paths = ft_strsplit(get_elem((*d)->env, "PATH"), ':');
	tmplist = list;
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
			list = listtmp;
			tmplist = list;
		}
	}
	free_tab(paths);
	return (list);
}
