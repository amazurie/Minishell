/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 16:35:12 by amazurie          #+#    #+#             */
/*   Updated: 2017/01/11 15:16:56 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_wstrlen(wchar_t *s)
{
	size_t i;
	size_t j;

	j = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] <= 0x7F)
			j++;
		else if (s[i] <= 0x7FF)
			j += 2;
		else if (s[i] <= 0xFFFF)
			j += 3;
		else if (s[i] <= 0x10FFFF)
			j += 4;
		i++;
	}
	return (j);
}
