/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 16:15:40 by amazurie          #+#    #+#             */
/*   Updated: 2016/12/12 15:24:24 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa(int n)
{
	char	*str;
	size_t	i;
	size_t	tmp;

	tmp = n;
	if (n < 0)
		tmp *= -1;
	i = ft_lennb(tmp) + (n < 0);
	if (!(str = ft_strnew(i + 1)))
		return (NULL);
	if (n == 0)
		str[0] = '0';
	while (tmp)
	{
		str[i] = tmp % 10 + '0';
		tmp /= 10;
		i--;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
