/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 11:38:14 by amazurie          #+#    #+#             */
/*   Updated: 2017/01/30 12:10:18 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strswap(char **s1, char **s2)
{
	char *str;

	if (*s1 && *s2)
	{
		str = ft_strdup(*s1);
		free (*s1);
		*s1 = ft_strdup(*s2);
		free (*s2);
		*s2 = ft_strdup(str);
		free(str);
	}
}
