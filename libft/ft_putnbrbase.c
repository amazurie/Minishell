/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrbase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 13:48:34 by amazurie          #+#    #+#             */
/*   Updated: 2017/01/11 13:18:48 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putbasenbr(size_t nb, char *base, size_t len)
{
	if (nb < len)
		ft_putchar(base[nb]);
	else
	{
		ft_putbasenbr(nb / len, base, len);
		ft_putbasenbr(nb % len, base, len);
	}
}

void		ft_putnbrbase(size_t nb, char *base)
{
	ft_putbasenbr(nb, base, ft_strlen(base));
}
