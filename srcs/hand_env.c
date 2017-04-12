/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 16:31:48 by amazurie          #+#    #+#             */
/*   Updated: 2017/04/12 15:38:12 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*char_to_lst(char **env)
{
	t_env	*envlst;
	t_env	*envtmp;
	t_env	*envtmp2;
	int		i;

	envlst = (t_env *)ft_memalloc(sizeof(t_env));
	envtmp = envlst;
	i = 0;
	while (env[i])
	{
		envtmp->elem = ft_strndup(env[i], ft_strlen_chr(env[i], '='));
		envtmp->cont = ft_strdup((env[i] + ft_strlen_chr(env[i], '=') + 1));
		envtmp->next = (t_env *)ft_memalloc(sizeof(t_env));
		envtmp2 = envtmp;
		envtmp = envtmp->next;
		i++;
	}
	free(envtmp);
	envtmp2->next = NULL;
	return (envlst);
}

void	set_env(t_env **env, char *elem, char *cont)
{
	t_env *tmpenv;

	if (!*env || !elem)
		return ;
	tmpenv = *env;
	while (tmpenv->next && ft_strcmp(tmpenv->elem, elem))
		tmpenv = tmpenv->next;
	if (!tmpenv->next && ft_strcmp(tmpenv->elem, elem))
	{
		tmpenv->next = (t_env *)ft_memalloc(sizeof(t_env));
		tmpenv = tmpenv->next;
		tmpenv->elem = ft_strdup(elem);
		tmpenv->cont = (!cont) ? NULL : ft_strdup(cont);
		tmpenv->next = NULL;
	}
	else
	{
		free(tmpenv->cont);
		tmpenv->cont = (!cont) ? NULL : ft_strdup(cont);
	}
}

void	unset_env(t_env **env, char *elem)
{
	t_env *tmpenv;
	t_env *tmp;
	t_env *tmp2;

	if (!*env || !elem)
		return ;
	tmpenv = *env;
	tmp = NULL;
	while (tmpenv && ft_strcmp(tmpenv->elem, elem))
	{
		tmp = tmpenv;
		tmpenv = tmpenv->next;
	}
	if (tmpenv && ft_strcmp(tmpenv->elem, elem) == 0)
	{
		tmp2 = tmpenv->next;
		free(tmpenv->elem);
		if (tmpenv->cont)
			free(tmpenv->cont);
		free(tmpenv);
		if (tmp)
			tmp->next = tmp2;
		else
			*env = tmp2;
	}
}

void	display_env(t_env *env, int c)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		if (c)
		{
			ft_putstr(LIGHTRED_COL);
			ft_putstr(tmp->elem);
			ft_putstr(DEFAULT_COL);
		}
		else
			ft_putstr(tmp->elem);
		ft_putchar('=');
		ft_putstr(tmp->cont);
		ft_putchar('\n');
		tmp = tmp->next;
	}
}

char	*get_elem(t_env *env, char *elem)
{
	while (env)
	{
		if (ft_strcmp(env->elem, elem) == 0)
			return (env->cont);
		env = env->next;
	}
	return (NULL);
}
