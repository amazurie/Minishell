/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 11:06:19 by amazurie          #+#    #+#             */
/*   Updated: 2017/05/24 16:16:28 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	built_in2(t_env **env, char **lstav, t_hist *hist)
{
	if (ft_strcmp(lstav[0], "history") == 0 && !lstav[1])
		display_hist(hist);
	else if (ft_strcmp(lstav[0], "cd") == 0)
		cd(lstav, *env);
	else if (ft_strcmp(lstav[0], "exit") == 0 && !lstav[1])
		return (-1);
	else if (ft_strcmp(lstav[0], "clear") == 0 && !lstav[1])
		ft_putstr_fd(tgetstr("cl", NULL), 0);
	else
		return (0);
	return (1);
}

int			built_in(t_env **env, char **lstav, t_hist *hist)
{
	int		i;

	i = 1;
	if (!lstav[0])
		return (0);
	else if (ft_strcmp(lstav[0], "env") == 0)
		envcom(lstav, *env, hist);
	else if (ft_strcmp(lstav[0], "setenv") == 0 && lstav[1])
		while (lstav[i])
			set_env(env, lstav[i++]);
	else if (ft_strcmp(lstav[0], "unsetenv") == 0 && lstav[1])
		unset_env(env, lstav);
	else if (ft_strcmp(lstav[0], "echo") == 0)
		echo_doing(lstav);
	else
		return (built_in2(env, lstav, hist));
	return (1);
}
