/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 16:31:48 by amazurie          #+#    #+#             */
/*   Updated: 2017/04/27 13:05:24 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env		*char_to_lst(char **env)
{
	t_env	*envlst;
	t_env	*envtmp;
	t_env	*envtmp2;
	int		i;

	if (!env || !*env)
		return (default_env());
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
	set_env(&envlst, "CLICOLOR=true");
	set_env(&envlst, "LSCOLORS=Gxfxcxdxbxegedabagacad");
	return (envlst);
}

void		del_elem(t_env **env, char *elem)
{
	t_env	*tmpenv;
	t_env	*tmp;
	t_env	*tmp2;

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

void		unset_env(t_env **env, char **lstav)
{
	int		i;

	if (!*env || !lstav | !lstav[1])
		return ;
	i = 0;
	while (lstav[i])
		del_elem(env, lstav[i++]);
}
