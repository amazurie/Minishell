/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 11:16:27 by amazurie          #+#    #+#             */
/*   Updated: 2017/06/27 10:44:21 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		change_envpwd(char *tmp, t_env *env)
{
	char	*tmp2;
	char	*tmp3;

	if ((tmp2 = ft_strjoin("OLDPWD=", get_elem(env, "PWD"))) == NULL)
		return (0);
	if ((tmp3 = ft_strjoin("PWD=", tmp)) == NULL)
		return (0);
	free(tmp);
	set_env(&env, tmp2);
	free(tmp2);
	set_env(&env, tmp3);
	free(tmp3);
	return (1);
}

char	*check_path(char *path, t_env *env)
{
	struct stat	atr;
	char		*tmp;

	if (chdir(path) == -1)
	{
		if (lstat(path, &atr) == -1)
			ft_putstr_fd("cd: no such file or directory: ", 2);
		else
			ft_putstr_fd("cd: permission denied: ", 2);
		ft_putstr_fd(path, 2);
		ft_putchar_fd('\n', 2);
		return (NULL);
	}
	if (path[0] == '/')
		return ((tmp = ft_strdup(path)));
	if (!(tmp = (char *)ft_memalloc(5001)))
	{
		chdir(get_elem(env, "PWD"));
		print_error("allocation error");
		return (NULL);
	}
	getcwd(tmp, 5000);
	return (tmp);
}

void	check_dotdot(char **tmp, char **path)
{
	size_t	i;

	if (!*tmp)
		return ;
	i = ft_strlen(*tmp) - 1;
	while (ft_strschr(*path, ".."))
	{
		ssupprchr(tmp, i--);
		while ((*path)[0] && (*path)[0] != '/')
			ssupprchr(path, 0);
		while ((*path)[0] && (*path)[0] == '/')
			ssupprchr(path, 0);
		while ((*tmp) && (*tmp)[i] != '/')
			ssupprchr(tmp, i--);
		if (!(*path)[0])
			while ((*tmp) && (*tmp)[i] == '/')
				ssupprchr(tmp, i--);
	}
}
