/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 12:42:31 by amazurie          #+#    #+#             */
/*   Updated: 2017/06/07 12:42:32 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*get_data(t_data *d)
{
	static t_data *d_save = NULL;

	if (d)
		d_save = d;
	return (d_save);
}

t_data	*data_alloc(char **env)
{
	t_data	*d;

	if ((d = (t_data *)ft_memalloc(sizeof(t_data))) == NULL)
		return (NULL);
	if ((d->env = char_to_lst(env)) == NULL)
		return (NULL);
	if ((d->line = (char *)ft_memalloc(2048)) == NULL)
		return (NULL);
	if ((d->buffline = (char *)ft_memalloc(2048)) == NULL)
		return (NULL);
	return (d);
}
