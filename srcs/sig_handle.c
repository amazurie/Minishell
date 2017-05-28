/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 11:04:32 by amazurie          #+#    #+#             */
/*   Updated: 2017/05/24 16:19:13 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_siginted(int sig)
{
	static int	sig_save;

	if (sig > 0)
		sig_save = sig;
	else if (sig == 0 && sig_save == 1)
	{
		sig_save = 0;
		return (1);
	}
	return (sig_save);
}

void	sig_reset(t_data **d, int **i)
{
	ft_memset((*d)->line, 0, (*i)[2]);
	(*i)[2] = 0;
	(*i)[3] = -1;
	(*i)[4] = 0;
	(*i)[5] = 0;
	(*i)[6] = 0;
	free((*d)->prompt);
	(*d)->prompt = get_prompt();
}
