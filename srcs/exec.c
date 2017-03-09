/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 15:28:15 by amazurie          #+#    #+#             */
/*   Updated: 2017/03/08 12:37:58 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <curses.h>
#include <term.h>

static int	test_paths(char **path)
{
	int	i;

	i = 0;
	while (path[i])
		if (access(path[i++], F_OK) == 0)
			return (i);
	return (0);
}

static int	built_in(e_list *env, char **lstav, h_list *hist)
{
	size_t	len;

	if (!lstav[0])
		return (0);
	else if (ft_strcmp(lstav[0], "env") == 0)
		display_env(env, lstav[1]);
	else if (ft_strcmp(lstav[0], "setenv") == 0 && lstav[1])
		set_env(&env, lstav[1], lstav[2]);
	else if (ft_strcmp(lstav[0], "unsetenv") == 0 && lstav[1])
		unset_env(&env, lstav[1]);
	else if (ft_strcmp(lstav[0], "pwd") == 0)
	{
		if (lstav[1])
			ft_putstr_fd("pwd: too many arguments", 2);
		else
			ft_putstr(get_elem(env, "PWD"));
		ft_putstr("\n");
	}
	else if (ft_strcmp(lstav[0], "history") == 0 && !lstav[1])
		display_hist(hist);
	else if (ft_strcmp(lstav[0], "cd") == 0)
		cd(lstav, env);
	else if (ft_strcmp(lstav[0], "exit") == 0 && !lstav[1])
		return (-1);
	else if (ft_strcmp(lstav[0], "clear") == 0 && !lstav[1])
		ft_putstr("\033c");
	else
		return (0);
	return (1);
}

int			exec(e_list *env, char *line, h_list *hist)
{
	char	**lstav;
	char	**paths;
	char	**fullpaths;
	int		i;
	int		j;
	pid_t	pid;

	if (!env)
		ft_putstr_fd("\e[31mNo environnement defined.\e[0m\n", 2);
	if (!env)
		return (-1);
	handbackslash(&line);
	lstav = ft_strsplit(line, ' ');
	line = get_elem(env, "PATH");
	paths = ft_strsplit(line, ':');
	if ((i = built_in(env, lstav, hist)))
		return (i);
	if (i == -1)
		exit(EXIT_SUCCESS);
	i = 0;
	while (paths[i])
		i++;
	fullpaths = (char **)ft_memalloc(sizeof(char *) * i);
	i = -1;
	while (paths[++i])
	{
		fullpaths[i] = ft_strjoin(paths[i], "/");
		fullpaths[i] = ft_strjoin(fullpaths[i], lstav[0]);
	}
	if (!test_paths(paths))
		return (0);
	while ((pid = fork()) == -1)
		sleep(2);
	i = 0;
	j = 0;
	if (pid > 0)
		wait(0);
	else
		while (fullpaths[i])
			if (execve(fullpaths[i++], lstav, NULL) != -1)
				j++;
	if (j < i)
	{
		ft_putstr_fd("\e[31mminishell:\e[0m command not found: ", 2);
		ft_putstr_fd(lstav[0], 2);
		ft_putstr_fd("\n", 2);
		exit(0);
	}
	return (0);
}
