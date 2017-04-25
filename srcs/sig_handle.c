/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 11:04:32 by amazurie          #+#    #+#             */
/*   Updated: 2017/04/25 11:59:05 by amazurie         ###   ########.fr       */
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
