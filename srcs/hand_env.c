/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 16:31:48 by amazurie          #+#    #+#             */
/*   Updated: 2017/03/03 16:31:50 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

e_list	*char_to_lst(char **env)
{
	e_list	*envlst;
	e_list	*envtmp;
	int		i;

	envlst = (e_list *)ft_memalloc(sizeof(e_list));
	envtmp = envlst;
	i = 0;
	while (env[i])
	{
		envtmp->elem = ft_strndup(env[i], ft_strlen_chr(env[i], '='));
		envtmp->cont = ft_strdup((env[i] + ft_strlen_chr(env[i], '=') + 1));
		envtmp->next = (e_list *)ft_memalloc(sizeof(e_list));
		envtmp = envtmp->next;
		i++;
	}
	envtmp->next = NULL;
	return (envlst);
}

void	set_env(e_list **env, char *elem, char *cont)
{
	e_list *tmpenv;

	tmpenv = *env;
	while (tmpenv->next && ft_strcmp(tmpenv->elem, elem))
		tmpenv = tmpenv->next;
	if (!tmpenv->next)
	{
		tmpenv->next = (e_list *)ft_memalloc(sizeof(e_list));
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

void	unset_env(e_list **env, char *elem)
{
	e_list *tmpenv;
	e_list *tmp;

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

void	display_env(e_list *env, char *opt)
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

char	*get_elem(e_list *env, char *elem)
{
	while (env->next)
	{
		if (ft_strcmp(env->elem, elem) == 0)
			return (env->cont);
		env = env->next;
	}
	return (NULL);
}
