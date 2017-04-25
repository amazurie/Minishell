/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 11:16:27 by amazurie          #+#    #+#             */
/*   Updated: 2017/04/25 17:43:32 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_path(char *path)
{
	if (chdir(path) == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putstr_fd(path, 2);
		ft_putchar_fd('\n', 2);
		return (0);
	}
	return (1);
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
