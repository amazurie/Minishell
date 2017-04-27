/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 12:25:37 by amazurie          #+#    #+#             */
/*   Updated: 2017/04/25 14:05:14 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_doing(t_env **env, char **lstav, t_hist *hist)
{
	size_t	j;
	int		i;
	char	*tmp;

	i = 1;
	if (lstav[1] && lstav[1][0] == '-' && lstav[1][1] == 'n')
		i++;
	while (lstav[i])
	{
		ft_putstr(lstav[i]);
		if (lstav[++i])
			ft_putchar(' ');
	}
	if (!lstav[1] || lstav[1][0] != '-' || lstav[1][1] != 'n')
		ft_putchar('\n');
}
