/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 12:20:44 by amazurie          #+#    #+#             */
/*   Updated: 2017/06/26 09:41:06 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_on_new(t_env **env, char *av)
{
	char	*elem;
	char	*cont;

	elem = ft_strndup(av, ft_strlen_chr(av, '='));
	cont = ft_strdup((av + ft_strlen_chr(av, '=') + 1));
	if ((*env = (t_env *)ft_memalloc(sizeof(t_env))) == NULL)
		return ;
	(*env)->elem = ft_strdup(elem);
	(*env)->cont = (!cont) ? NULL : ft_strdup(cont);
	(*env)->next = NULL;
	free(cont);
	free(elem);
	return ;
}

static void	add_elem(t_env **tmpenv, char *elem, char *cont)
{
	if (!((*tmpenv)->next = (t_env *)ft_memalloc(sizeof(t_env))))
		return ;
	(*tmpenv) = (*tmpenv)->next;
	(*tmpenv)->elem = ft_strdup(elem);
	(*tmpenv)->cont = (!cont) ? NULL : ft_strdup(cont);
	(*tmpenv)->next = NULL;
}

void		set_env(t_env **env, char *av)
{
	t_env	*tmpenv;
	char	*elem;
	char	*cont;

	if (!av)
		return ;
	if (!*env)
		return (set_on_new(env, av));
	elem = ft_strndup(av, ft_strlen_chr(av, '='));
	cont = ft_strdup((av + ft_strlen_chr(av, '=') + 1));
	tmpenv = *env;
	while (tmpenv->next && ft_strcmp(tmpenv->elem, elem))
		tmpenv = tmpenv->next;
	if (!tmpenv->next && ft_strcmp(tmpenv->elem, elem))
	{
		add_elem(&tmpenv, elem, cont);
		free(elem);
		free(cont);
		return ;
	}
	free(tmpenv->cont);
	tmpenv->cont = (!cont) ? NULL : ft_strdup(cont);
	free(elem);
	free(cont);
}
