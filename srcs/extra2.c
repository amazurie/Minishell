/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 13:44:01 by amazurie          #+#    #+#             */
/*   Updated: 2017/03/01 14:23:15 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handbackslash(char **s)
{
	size_t i;

	i = 0;
	while ((*s)[i] && (*s)[i + 1])
	{
		if ((*s)[i] == '\\' && (*s)[i + 1] != '\\')
			ssupprchr(s, i);
		else if ((*s)[i] == '\\' && (*s)[i + 1] == '\\')
		{
			if ((*s)[i + 2] == ';')
			{
				ssupprchr(s, i);
				ssupprchr(s, i + 1);
			}
			else
				ssupprchr(s, i);
		}
		i++;
	}
}

void	display_prompt(char *pwd)
{
	int		i;

	i = ft_strlen(pwd);
	while (i > 0 && pwd[i] != '/')
		i--;
	ft_putstr(PROMPT_COL);
	ft_putstr("$");
	ft_putstr((pwd + i + 1));
	ft_putstr("> ");
	ft_putstr(DEFAULT_COL);
}
