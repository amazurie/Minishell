/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 15:13:41 by amazurie          #+#    #+#             */
/*   Updated: 2017/03/15 13:23:07 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_dotdot(char **path)
{
	int	i;
	int	j;

	i = 0;
	while ((i = ft_strschr_len((*path + i), "..")))
	{
		j = ft_strlen_chr((*path + 1), '/');
		i = i + 2;
		while (path[0][i] != '/')
			ssupprchr(path, i--);
		ssupprchr(path, i--);
		while (path[0][i] != '/')
			ssupprchr(path, i--);
		ssupprchr(path, i--);
	}
	if (!path[0][0])
		ft_strcat(*path, "/");
}

static void	change_pwd(char *path, e_list *env)
{
	char *tmp;
	char *tmp2;

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
		tmp = ft_strjoin(get_elem(env, "PWD"), "/");
		tmp2 = ft_strjoin(tmp, path);
		free(tmp);
	}
	else
		tmp2 = ft_strdup(path);
	check_dotdot(&tmp2);
	set_env(&env, "PWD", tmp2);
	free(tmp2);
}

static void	check_pwd2(char *path, e_list *env, char *rep, char *tmp)
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

static int	check_pwd(char *path, e_list *env, char *rep)
{
	char	*tmp;
	char	*tmp2;
	size_t	i;
	size_t	j;

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
	free(tmp);
	return (0);
}

int			cd(char **path, e_list *env)
{
	char	*tmp;
	int		i;

	i = 0;
	while (path[i])
		i++;
	if (i > 3)
		ft_putstr_fd("cd: too many arguments\n", 2);
	else if (i == 3)
		return (check_pwd(path[1], env, path[2]));
	else
	{
		if (i == 1)
			tmp = ft_strdup(get_elem(env, "HOME"));
		else if (ft_strcmp(path[1], "-") == 0)
			tmp = ft_strdup(get_elem(env, "OLDPWD"));
		else
			tmp = ft_strdup(path[1]);
		change_pwd(tmp, env);
		free(tmp);
	}
	return (0);
}
