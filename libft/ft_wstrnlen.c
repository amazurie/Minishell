/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrnlen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:33:03 by amazurie          #+#    #+#             */
/*   Updated: 2017/01/12 11:39:42 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_wstrnlen(wchar_t *str, size_t len, size_t i)
{
	if (!*str || !len)
		return (i);
	if (*str <= 0x7F)
		return (ft_wstrnlen(++str, --len, i + 1));
	if (*str <= 0x7FF && len >= 2)
		return (ft_wstrnlen(++str, len - 2, i + 2));
	if (*str <= 0xFFFF && len >= 3)
		return (ft_wstrnlen(++str, len - 3, i + 3));
	if (*str <= 0x10FFFF && len >= 4)
		return (ft_wstrnlen(++str, len - 4, i + 4));
	return (i);
}
