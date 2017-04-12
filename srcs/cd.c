/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 15:13:41 by amazurie          #+#    #+#             */
/*   Updated: 2017/04/12 10:31:34 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_pwd(char *path, t_env *env)
{
	char	*tmp;

	if (chdir(path) == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putstr_fd(path, 2);
		ft_putchar_fd('\n', 2);
		return ;
	}
	set_env(&env, "OLDPWD", get_elem(env, "PWD"));
	if (path[0] != '/')
	{
		tmp = (char *)ft_memalloc(5001);
		getcwd(tmp, 5000);
	}
	else
		tmp = ft_strdup(path);
	set_env(&env, "PWD", tmp);
	free(tmp);
}

static void	check_pwd2(char *path, t_env *env, char *rep, char *tmp)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strschr_len(tmp, path);
	while (tmp[j] == path[i++])
		ssupprchr(&tmp, j);
	i = 0;
	while (rep[i])
		saddchr(&tmp, rep[i++], j++);
	if (ft_strcmp(tmp, get_elem(env, "PWD")) != 0)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putstr_fd(tmp, 2);
		ft_putchar_fd('\n', 2);
	}
	else
	{
		i = ft_strlen(get_elem(env, "HOME"));
		while (tmp[0] && i-- > 0)
			ssupprchr(&tmp, 0);
		ft_putchar('~');
		ft_putstr(tmp);
		ft_putchar('\n');
	}
}

static int	check_pwd(char *path, t_env *env, char *rep)
{
	char	*tmp;
	char	*tmp2;

	if (!get_elem(env, "HOME"))
	{
		ft_putstr_fd("cd: HOME not set.\n", 2);
		return (0);
	}
	else if (!(tmp = ft_strdup(get_elem(env, "PWD"))))
		ft_putstr_fd("cd: PWD not set.\n", 2);
	else if ((tmp2 = ft_strschr(tmp, path)) == 0)
	{
		ft_putstr_fd("cd: string not in pwd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putchar_fd('\n', 2);
	}
	else
		check_pwd2(path, env, rep, tmp);
	if (tmp)
		free(tmp);
	return (0);
}

char		*cd2(char **path, t_env *env, int i)
{
	char	*tmp;

	if (i == 1 || ft_strcmp(path[1], "~") == 0)
	{
		if (!get_elem(env, "HOME"))
			ft_putstr_fd("cd: HOME not set.\n", 2);
		else
			tmp = ft_strdup(get_elem(env, "HOME"));
	}
	else if (ft_strcmp(path[1], "-") == 0)
	{
		if (!get_elem(env, "OLDPWD"))
		{
			ft_putstr_fd("cd: OLDPWD not set.\n", 2);
			return (NULL);
		}
		else
			tmp = ft_strdup(get_elem(env, "OLDPWD"));
	}
	tmp = ft_strdup(path[1]);
	return (tmp);
}

int			cd(char **path, t_env *env)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	while (path[i])
		i++;
	if (i > 3)
		ft_putstr_fd("cd: too many arguments\n", 2);
	else if (i == 3)
		return (check_pwd(path[1], env, path[2]));
	else
	{
		if (!(tmp = cd2(path, env, i)))
			return (-1);
		if (tmp)
			change_pwd(tmp, env);
		free(tmp);
	}
	return (0);
}
