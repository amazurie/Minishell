/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 13:40:05 by amazurie          #+#    #+#             */
/*   Updated: 2017/01/30 15:35:45 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_handle_itoa_base(size_t nb, char *base, char *s, int *i)
{
	size_t len;

	len = ft_strlen(base);
	if (nb < len)
		s[(*i)++] = base[nb];
	else
	{
		ft_handle_itoa_base(nb / len, base, s, i);
		ft_handle_itoa_base(nb % len, base, s, i);
	}
	s[*i] = 0;
}

char		*ft_itoa_base(size_t nb, char *base)
{
	int		i;
	char	*s;

	i = 0;
	s = (char *)ft_memalloc(sizeof(int) * ft_lennb(nb) + 1);
	ft_handle_itoa_base(nb, base, s, &i);
	return (s);
}
