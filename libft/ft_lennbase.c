/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lennbase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 11:36:14 by amazurie          #+#    #+#             */
/*   Updated: 2017/01/12 11:36:16 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_lennbase(size_t n, char *base)
{
	size_t i;
	size_t len;

	i = 0;
	len = ft_strlen(base);
	while ((n /= len) > 0)
		i++;
	return (++i);
}
