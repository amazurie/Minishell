/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 12:25:37 by amazurie          #+#    #+#             */
/*   Updated: 2017/06/20 12:49:00 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	echo_env(char **lstav, t_env **env, size_t i)
{
	char	*tmp;
	size_t	j;

	if ((j = ft_strlen_chr(lstav[i], '$')) < ft_strlen(lstav[i]))
	{
		ft_putnstr_fd(lstav[i], 0, j);
		j = 0;
		while (j < ft_strlen(lstav[i]))
		{
			j += ft_strlen_chr((lstav[i] + j), '$');
			if (ft_strlen_chr((lstav[i] + j + 1), '$'))
				tmp = ft_strndup((lstav[i] + j + 1),
						ft_strlen_chr((lstav[i] + j + 1), '$'));
			else
				tmp = ft_strdup((lstav[i] + j));
			j += ft_strlen(tmp);
			ft_putstr_fd(get_elem(*env, tmp), 0);
			free(tmp);
			j = (j == 0) ? 1 : j;
		}
		return (1);
	}
	return (0);
}

void		echo_doing(char **lstav, t_env **env)
{
	size_t	i;

	i = 1;
	if (lstav[1] && lstav[1][0] == '-' && lstav[1][1] == 'n')
		i++;
	while (lstav[i])
	{
		if (!echo_env(lstav, env, i))
			ft_putstr_fd(lstav[i], 0);
		if (lstav[++i])
			ft_putchar_fd(' ', 0);
	}
	if (!lstav[1] || lstav[1][0] != '-' || lstav[1][1] != 'n')
		ft_putchar_fd('\n', 0);
}
