/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 15:28:15 by amazurie          #+#    #+#             */
/*   Updated: 2017/06/07 13:22:21 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			test_perm(char *path)
{
	struct stat	atr;

	if (access(path, F_OK) != -1 && (lstat(path, &atr) != 0
				|| !(atr.st_mode & S_IXUSR)))
	{
		ft_putstr_fd("\e[31mminishell:\e[0m permission denied: ", 2);
		ft_putstr_fd(path, 2);
		ft_putchar_fd('\n', 2);
		exit(0);
		return (0);
	}
	return (1);
}

static void	fork_exec2(char **lstav, t_env **env, char **tmpenv)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = test_absolute(lstav[0]);
	if (execve(tmp, lstav, tmpenv) == -1)
	{
		if (!*env)
			ft_putstr_fd("\e[31mNo environnement defined.\e[0m\n", 2);
		else if (test_perm(tmp) == 0)
		{
			free(tmp);
			return ;
		}
	}
	free(tmp);
	if (*env)
	{
		ft_putstr_fd("\e[31mminishell:\e[0m command not found: ", 2);
		ft_putstr_fd(lstav[0], 2);
		ft_putstr_fd("\n", 2);
	}
	exit(0);
}

static void	forkexec(char **lstav, char **fullpaths, char **tmpenv, t_env **env)
{
	pid_t		pid;
	int			i;
	int			j;

	while ((pid = fork()) == -1)
		sleep(2);
	i = 0;
	j = 0;
	if (pid > 0)
		wait(0);
	else if (fullpaths != NULL)
	{
		while (fullpaths[i++])
		{
			if (execve(fullpaths[i - 1], lstav, tmpenv) != -1)
				j++;
			else if (test_perm(fullpaths[i]) == 0)
				return ;
		}
	}
	else
		i = j + 1;
	if (j < i)
		fork_exec2(lstav, env, tmpenv);
}

static void	exec2(char **lstav, char **paths, char **fullpaths, t_env **env)
{
	char	**tmpenv;
	char	*tmp;
	int		i;

	i = 0;
	while (paths && paths[i])
		i++;
	if (i)
		fullpaths = (char **)ft_memalloc(sizeof(char *) * (i + 1));
	else
		fullpaths = NULL;
	i = 0;
	while (paths && paths[i] && fullpaths)
	{
		tmp = ft_strjoin(paths[i], "/");
		fullpaths[i++] = ft_strjoin(tmp, lstav[0]);
		free(tmp);
	}
	tmpenv = lst_to_char(*env);
	forkexec(lstav, fullpaths, tmpenv, env);
	free_tab(tmpenv);
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
	if ((lstav = ft_strsplit(line, ' ')) == NULL)
		return (0);
	paths = ft_strsplit(get_elem(*env, "PATH"), ':');
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
