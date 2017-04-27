/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 15:51:39 by amazurie          #+#    #+#             */
/*   Updated: 2017/04/27 12:59:46 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	hand_u(char *uelem, t_env **envcpy, size_t *i)
{
	char **tmp;

	if (!uelem)
	{
		ft_putstr_fd("env: option requires an arguments -- u\n", 2);
		ft_putstr_fd("usage [-i] [-u name] [utility [arguments]]\n", 2);
		i[2] = 0;
	}
	else if (ft_strchr(uelem, '='))
	{
		ft_putstr_fd("env: unsetenv ", 2);
		ft_putstr_fd(uelem, 2);
		ft_putstr_fd(": Invalid argument\n", 2);
		i[2] = 0;
	}
	else
		del_elem(envcpy, uelem);
}

void		builtu_env(char **lstav, t_env **envcpy, size_t *i)
{
	if (lstav[i[0]][i[1] + 1])
	{
		hand_u((lstav[i[0]] + ft_strlen_chr(lstav[i[0]], 'u') + 1), envcpy, i);
		i[1] = ft_strlen(lstav[i[0]]);
	}
	else if (lstav[i[0] + 1])
		hand_u(lstav[++i[0]], envcpy, i);
	else
	{
		hand_u(NULL, envcpy, i);
		i[2] = 0;
	}
	i[3] = 1;
}
