/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnwstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 11:36:47 by amazurie          #+#    #+#             */
/*   Updated: 2017/01/12 11:36:48 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnwstr(wchar_t *s, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i] && j < n)
	{
		if (s[i] <= 0x7F)
			j++;
		else if (s[i] <= 0x7FF)
			j += 2;
		else if (s[i] <= 0xFFFF)
			j += 3;
		else if (s[i] <= 0x10FFFF)
			j += 4;
		if (j <= n)
			ft_putwchar(s[i]);
		i++;
	}
}
