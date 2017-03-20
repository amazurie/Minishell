/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 13:44:01 by amazurie          #+#    #+#             */
/*   Updated: 2017/03/15 15:10:12 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handbackslash(char **s)
{
	size_t i;

	i = 0;
	while ((*s)[i] && (*s)[i + 1])
	{
		if ((*s)[i] == '\\' && (*s)[i + 1] != '\\')
			ssupprchr(s, i);
		else if ((*s)[i] == '\\' && (*s)[i + 1] == '\\')
		{
			if ((*s)[i + 2] == ';')
			{
				ssupprchr(s, i);
				ssupprchr(s, i + 1);
			}
			else
				ssupprchr(s, i);
		}
		i++;
	}
}

void	display_prompt(char *pwd)
{
	int		i;

	if (pwd)
	{
		i = ft_strlen(pwd);
		while (i > 0 && pwd[i] != '/')
			i--;
	}
	else
		i = 0;
	ft_putstr(PROMPT_COL);
	ft_putstr("$");
	if (i)
		ft_putstr((pwd + i + 1));
	else if (!pwd)
		ft_putstr("@?");
	ft_putstr("> ");
	ft_putstr(DEFAULT_COL);
}

void	free_tab(char **tab)
{
	int i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

int		test_paths(char **path)
{
	int	i;

	if (!path || !*path)
		return (0);
	i = 0;
	while (path[i])
		if (access(path[i++], F_OK) == 0)
			return (i);
	return (0);
}

char	*test_absolute(t_env *env, char *command)
{
	struct stat	atr;
	char		*path;
	char		*tmp;
	int			i;

	if (!env || !command)
		return (NULL);
	tmp = ft_strjoin(get_elem(env, "PWD"), "\\");
	path = ft_strjoin(tmp, command);
	stat(path, &atr);
	if (atr.st_mode == 'b')
		return (path);
	free(path);
	return (NULL);
}
