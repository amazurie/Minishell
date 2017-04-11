/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 11:07:35 by amazurie          #+#    #+#             */
/*   Updated: 2017/04/11 15:59:11 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	built_env(char **lstav, t_env **envcpy, size_t *i)
{
	i[1] = 0;
	while (lstav[i[0]][++i[1]] && lstav[i[0]][0] == '-')
	{
		if (lstav[i[0]][i[1]] == 'i')
			del_env(envcpy);
		else if (lstav[i[0]][i[1]] == 'u')
			builtu_env(lstav, envcpy, i);
		else if (lstav[i[0]][i[1]] == 'c')
			i[2] = 2;
		else
		{
			ft_putstr_fd("env: illegal option -- ", 2);
			ft_putchar_fd(lstav[i[0]][i[1]], 2);
			ft_putstr_fd("\nusage [-i] [-u name] [utility [arguments]]\n", 2);
			while (lstav[i[0]])
				i[0]++;
			i[2] = 0;
			i[0]--;
			i[1] = ft_strlen(lstav[i[0]]);
		}
	}
}

static void	envexec(char **lstav, t_env **envcpy, t_hist *hist, size_t *i)
{
	char	**tmp;

	tmp = (char **)ft_memalloc(sizeof(char *) * 3);
	tmp[1] = ft_strdup(lstav[i[0]++]);
	while (lstav[i[0]])
	{
		tmp[0] = ft_strjoin(tmp[1], " ");
		free(tmp[1]);
		tmp[1] = ft_strjoin(tmp[0], lstav[i[0]++]);
		free(tmp[0]);
	}
	exec(envcpy, tmp[1], hist);
	free(tmp[1]);
	free(tmp);
	i[2] = 0;
	i[0]--;
}

static void	envcom2(char **lstav, t_env **envcpy, t_hist *hist)
{
	size_t	*i;

	i = (size_t *)ft_memalloc(sizeof(size_t) * 4);
	i[0] = 0;
	i[2] = 1;
	while (lstav[++i[0]])
	{
		built_env(lstav, envcpy, i);
		if (!lstav[i[0]][1] && lstav[i[0]][0] == '-')
			del_env(envcpy);
		if (lstav[i[0]] && lstav[i[0]][0] != '-'
				&& (!ft_strchr(lstav[i[0] - 1], 'u')
				|| lstav[i[0] - 1][ft_strlen_chr(lstav[i[0] - 1], 'u') + 1]))
			envexec(lstav, envcpy, hist, i);
	}
	if (i[2])
		display_env(*envcpy, (i[2] == 2) ? 1 : 0);
	free(i);
}

void		envcom(char **lstav, t_env *env, t_hist *hist)
{
	t_env *envcpy;

	if (!lstav[1])
		display_env(env, 0);
	else
	{
		envcpy = env_cpy(env);
		envcom2(lstav, &envcpy, hist);
		del_env(&envcpy);
	}
}
