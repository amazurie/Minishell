/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 11:16:27 by amazurie          #+#    #+#             */
/*   Updated: 2017/04/03 12:34:34 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_dotdot(char **tmp, char **path)
{
	size_t	i;
	size_t	j;

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
