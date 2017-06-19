/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 16:30:59 by amazurie          #+#    #+#             */
/*   Updated: 2017/06/13 11:23:39 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		print_error(char *s)
{
	ft_putstr_fd(ERR_COL, 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(DEFAULT_COL, 2);
	ft_putchar_fd('\n', 2);
	return (0);
}
