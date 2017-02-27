/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 14:05:06 by amazurie          #+#    #+#             */
/*   Updated: 2016/12/06 15:56:00 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include <stdio.h>

t_line	*init(int fd, t_line *tmp)
{
	if (!tmp)
		return (NULL);
	while (tmp->next && tmp->fd != fd)
		tmp = tmp->next;
	if (tmp->fd == fd)
		return (tmp);
	if (!(tmp->next = (t_line *)ft_memalloc(sizeof(t_line))))
		return (NULL);
	tmp = tmp->next;
	if (!(tmp->line = (char *)ft_memalloc(BUFF_SIZE + 1)))
		return (NULL);
	tmp->fd = fd;
	return (tmp);
}

int		read_file(int fd, t_line *tmp, char **line)
{
	char	*buff;
	int		ret;
	int		endl;
	char	*tmp2;

	endl = (ft_strchr(tmp->line, DELIMITER)) ? 1 : 0;
	buff = (char*)ft_memalloc(BUFF_SIZE + 1);
	ret = 1;
	while (!endl && ret > 0)
	{
		if ((ret = read(fd, buff, BUFF_SIZE)) < 0)
			return (-1);
		if (!(tmp2 = ft_strnjoin(tmp->line, buff, ft_strlen(tmp->line) + ret)))
			return (-1);
		free(tmp->line);
		tmp->line = tmp2;
		endl = (ft_strchr(tmp->line, DELIMITER)) ? 1 : 0;
	}
	free(buff);
	if (!(ret = (int)ft_strlen(tmp->line)))
		return (0);
	endl = ft_strlen_chr(tmp->line, DELIMITER);
	*line = ft_strndup(tmp->line, endl);
	tmp->line = ft_strsub(tmp->line, endl + 1, ft_strlen(tmp->line) - endl);
	return ((ret > 0));
}

int		get_next_line(const int fd, char **line)
{
	static t_line	*lect = NULL;
	t_line			*tmp;

	if ((read(fd, 0, 0)) < 0)
		return (-1);
	if (!lect)
	{
		if (!(lect = (t_line *)ft_memalloc(sizeof(t_line))))
			return (-1);
		if (!(lect->line = (char *)ft_memalloc(BUFF_SIZE + 1)))
			return (-1);
		lect->fd = fd;
		lect->next = NULL;
	}
	tmp = lect;
	tmp = init(fd, tmp);
	return (read_file(fd, tmp, line));
}
