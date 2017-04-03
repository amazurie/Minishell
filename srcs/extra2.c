/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 13:44:01 by amazurie          #+#    #+#             */
/*   Updated: 2017/04/03 16:41:59 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_prompt(char *pwd)
{
	int		i;

	if (pwd)
	{
		i = ft_strlen(pwd);
		if (i == 1)
			return (pwd);
		while (i > 0 && pwd[i] != '/')
			i--;
	}
	else
		i = -1;
	if (i >= 0)
		return ((pwd + i + 1));
	return ("@?");
}

void	display_prompt(char *pwd)
{
	ft_putstr(PROMPT_COL);
	ft_putstr("$");
	ft_putstr(pwd);
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

char	*test_absolute(char *command)
{
	char		*path;
	int			i;

	if (!command)
		return (NULL);
	path = ft_strdup(command);
	if (access(path, F_OK) == -1)
		ft_bzero(path, ft_strlen(path));
	return (path);
}
