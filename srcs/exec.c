/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 15:28:15 by amazurie          #+#    #+#             */
/*   Updated: 2017/04/25 16:23:49 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <curses.h>
#include <term.h>

static void	fork_exec2(char **lstav, t_env **env, char **tmpenv)
{
	char	*tmp;

	tmp = test_absolute(lstav[0]);
	if (execve(tmp, lstav, tmpenv) == -1)
		if (!*env)
			ft_putstr_fd("\e[31mNo environnement defined.\e[0m\n", 2);
	free(tmp);
	if (*env)
	{
		ft_putstr_fd("\e[31mminishell:\e[0m command not found: ", 2);
		ft_putstr_fd(lstav[0], 2);
		ft_putstr_fd("\n", 2);
	}
	exit(0);
}

static void	fork_exec(char **lstav, char **fullpaths, t_env **env)
{
	pid_t	pid;
	char	**tmpenv;
	size_t	i;
	size_t	j;

	while ((pid = fork()) == -1)
		sleep(2);
	tmpenv = lst_to_char(*env);
	i = 0;
	j = 0;
	if (pid > 0)
		wait(0);
	else if (fullpaths != NULL)
	{
		while (fullpaths[i])
			if (execve(fullpaths[i++], lstav, tmpenv) != -1)
				j++;
	}
	else
		i = j + 1;
	if (j < i)
		fork_exec2(lstav, env, tmpenv);
	free_tab(tmpenv);
}

static void	exec2(char **lstav, char **paths, char **fullpaths, t_env **env)
{
	char	*tmp;
	size_t	i;

	i = 0;
	while (paths && paths[i])
		i++;
	if (i)
		fullpaths = (char **)ft_memalloc(sizeof(char *) * (i + 1));
	else
		fullpaths = NULL;
	i = 0;
	while (paths && paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		fullpaths[i++] = ft_strjoin(tmp, lstav[0]);
		free(tmp);
	}
	fork_exec(lstav, fullpaths, env);
	i = 0;
	while (paths && paths[i])
		free(fullpaths[i++]);
	free(fullpaths);
}

int			exec(t_env **env, char *line, t_hist *hist)
{
	char	**lstav;
	char	**paths;
	char	**fullpaths;
	int		i;

	fullpaths = NULL;
	handbackslash(&line);
	lstav = ft_strsplit(line, ' ');
	line = get_elem(*env, "PATH");
	paths = ft_strsplit(line, ':');
	if ((i = built_in(env, lstav, hist)))
	{
		free_tab(paths);
		free_tab(lstav);
	}
	if (i)
		return (i);
	exec2(lstav, paths, fullpaths, env);
	free_tab(paths);
	free_tab(lstav);
	return (0);
}
