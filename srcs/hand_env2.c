/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand_env2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 11:08:02 by amazurie          #+#    #+#             */
/*   Updated: 2017/04/03 11:08:03 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_env(t_env **env)
{
	t_env	*e;
	t_env	*e2;

	if (!(*env))
		return ;
	while ((*env))
	{
		e = (*env);
		(*env) = (*env)->next;
		free(e->elem);
		free(e->cont);
		free(e);
	}
	(*env) = NULL;
}

t_env	*env_cpy(t_env *env)
{
	t_env *envcpy;
	t_env *tmp;
	t_env *tmp2;
	t_env *tmp3;

	tmp = env;
	envcpy = (t_env *)ft_memalloc(sizeof(t_env));
	tmp2 = envcpy;
	while (tmp)
	{
		tmp2->elem = ft_strdup(tmp->elem);
		tmp2->cont = ft_strdup(tmp->cont);
		tmp2->next = (t_env *)ft_memalloc(sizeof(t_env));
		tmp3 = tmp2;
		tmp2 = tmp2->next;
		tmp = tmp->next;
	}
	free(tmp2);
	tmp3->next = NULL;
	return (envcpy);
}
