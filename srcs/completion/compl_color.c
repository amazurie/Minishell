/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compl_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 11:29:22 by amazurie          #+#    #+#             */
/*   Updated: 2017/06/07 11:29:23 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	file_type(mode_t mode)
{
	if (S_ISLNK(mode))
		return ('l');
	if (S_ISDIR(mode))
		return ('d');
	if (S_ISCHR(mode))
		return ('c');
	if (S_ISBLK(mode))
		return ('b');
	if (S_ISFIFO(mode))
		return ('p');
	if (S_ISSOCK(mode))
		return ('s');
	if (mode & S_IXUSR)
		return ('e');
	if (S_ISREG(mode))
		return ('-');
	return ('?');
}

static char	*compl_color(char *av)
{
	struct stat	atr;

	if (lstat(av, &atr) == -1)
		return (NULL);
	if (file_type(atr.st_mode) == 'd')
		return ("\e[1;36m");
	if (file_type(atr.st_mode) == 'l')
		return ("\e[35m");
	if (file_type(atr.st_mode) == 'e')
		return ("\e[31m");
	return ("\e[39m");
}

void		compl_addcolor(t_arg **tmplist, char *path, char *arg)
{
	char *tmp;
	char *tmp2;

	if (path != NULL)
	{
		if (!(tmp = ft_strjoin(path, "/")))
		{
			(*tmplist)->color = NULL;
			return ;
		}
		if (!(tmp2 = ft_strjoin(tmp, arg)))
		{
			free(tmp);
			(*tmplist)->color = NULL;
			return ;
		}
		(*tmplist)->color = compl_color(tmp2);
		free(tmp);
		free(tmp2);
	}
	else
		(*tmplist)->color = NULL;
}
