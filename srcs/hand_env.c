/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 16:31:48 by amazurie          #+#    #+#             */
/*   Updated: 2017/03/15 15:09:12 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*char_to_lst(char **env)
{
	t_env	*envlst;
	t_env	*envtmp;
	int		i;

	envlst = (t_env *)ft_memalloc(sizeof(t_env));
	envtmp = envlst;
	i = 0;
	while (env[i])
	{
		envtmp->elem = ft_strndup(env[i], ft_strlen_chr(env[i], '='));
		envtmp->cont = ft_strdup((env[i] + ft_strlen_chr(env[i], '=') + 1));
		envtmp->next = (t_env *)ft_memalloc(sizeof(t_env));
		envtmp = envtmp->next;
		i++;
	}
	envtmp->next = NULL;
	return (envlst);
}

void	set_env(t_env **env, char *elem, char *cont)
{
	t_env *tmpenv;

	tmpenv = *env;
	while (tmpenv->next && ft_strcmp(tmpenv->elem, elem))
		tmpenv = tmpenv->next;
	if (!tmpenv->next)
	{
		tmpenv->next = (t_env *)ft_memalloc(sizeof(t_env));
		tmpenv = tmpenv->next;
		tmpenv->elem = (ft_strdup(elem));
		tmpenv->cont = (ft_strdup(cont));
		tmpenv->next = NULL;
	}
	else
	{
		free(tmpenv->cont);
		if (!cont)
			tmpenv->cont = NULL;
		else
			tmpenv->cont = ft_strdup(cont);
	}
}

void	unset_env(t_env **env, char *elem)
{
	t_env *tmpenv;
	t_env *tmp;

	tmpenv = *env;
	while (tmpenv->next && ft_strcmp(tmpenv->elem, elem))
	{
		tmp = tmpenv;
		tmpenv = tmpenv->next;
	}
	if (ft_strcmp(tmpenv->elem, elem) == 0)
	{
		free(tmpenv->elem);
		free(tmpenv->cont);
		if (tmp)
			tmp->next = tmpenv->next;
		else
			tmp = tmpenv->next;
		free(tmpenv);
	}
}

void	display_env(t_env *env, char *opt)
{
	if (opt && ft_strcmp(opt, "color") != 0)
	{
		ft_putstr_fd("env: illegal option -- ", 2);
		ft_putstr_fd(opt, 2);
		ft_putstr_fd("\n", 2);
		ft_putstr_fd("usage: env [color]", 2);
		ft_putstr_fd("\n", 2);
		return ;
	}
	while (env->next)
	{
		if (opt && ft_strcmp(opt, "color") == 0)
			ft_putstr(LIGHTRED_COL);
		ft_putstr(env->elem);
		if (opt && ft_strcmp(opt, "color") == 0)
			ft_putstr(DEFAULT_COL);
		ft_putchar('=');
		ft_putstr(env->cont);
		ft_putchar('\n');
		env = env->next;
	}
}

char	*get_elem(t_env *env, char *elem)
{
	while (env->next)
	{
		if (ft_strcmp(env->elem, elem) == 0)
			return (env->cont);
		env = env->next;
	}
	return (NULL);
}
