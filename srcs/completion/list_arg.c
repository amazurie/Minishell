#include "minishell.h"

t_arg	*list_content(char *path, char *word)
{
	struct dirent	*dirc;
	DIR				*dirp;
	t_arg			*list;
	t_arg			*tmplist;
	t_arg			*listtmp;
	int				i;

	if (!(dirp = opendir(path)))
		return (NULL);
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
		if (ft_strncmp(word, dirc->d_name, ft_strlen(word)) == 0 || !word[0])
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

t_arg	*list_arg(t_data **d, int **i)
{
	t_arg	*list;
	t_arg	*tmplist;
	t_arg	*listtmp;
	char	**paths;
	char	*word;
	int		j;

	word = recover_wtocompl(d, i);
	paths = ft_strsplit(get_elem((*d)->env, "PATH"), ':');
	j = 0;
	if (!(list = list_content(word, word)))
		list = list_content(".", word);
	if (check_command(d, i) == 1)
		return (list);
	while (paths && paths[j])
	{
		tmplist = list;
		list = list_content(paths[j++], word);
		if (list)
		{
			listtmp = list;
			while (listtmp->next)
				listtmp = listtmp->next;
			listtmp->next = tmplist;
		}
	}
	free(word);
	free_tab(paths);
	return (list);
}
