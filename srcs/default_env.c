/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 15:27:38 by amazurie          #+#    #+#             */
/*   Updated: 2017/05/24 16:29:25 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*default_env(void)
{
	t_env	*env;
	t_env	*envtmp;
	char	*tmp;

	if ((tmp = ft_memalloc(5000)) == NULL)
		return (NULL);
	if ((env = (t_env *)ft_memalloc(sizeof(t_env))) == NULL)
		return (NULL);
	envtmp = env;
	envtmp->elem = ft_strdup("PWD");
	getcwd(tmp, 4999);
	envtmp->cont = ft_strdup(tmp);
	if ((envtmp->next = (t_env *)ft_memalloc(sizeof(t_env))) == NULL)
		return (NULL);
	envtmp = envtmp->next;
	envtmp->elem = ft_strdup("_");
	envtmp->cont = ft_strdup("/usr/bin/env");
	envtmp->next = NULL;
	return (env);
}
