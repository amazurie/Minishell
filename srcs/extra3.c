/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 11:08:40 by amazurie          #+#    #+#             */
/*   Updated: 2017/04/03 16:58:17 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_onlytab(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] != '\t')
			return (0);
	return (1);
}

void	erase_printline(t_data **d, int **i)
{
	char	*temp;
	int		j;

	j = ft_strlen((*d)->prompt) + 3;
	(*i)[1] = 0;
	while ((*d)->line[(*i)[1]])
		if ((*d)->line[(*i)[1]++] == '\t')
			j += 7;
	(*i)[1] = 0;
	temp = (char *)ft_memalloc((*i)[2] + j + 1);
	ft_memset(temp, '\b', j + (*i)[4]);
	ft_memset(temp, '\b', j + (*i)[4]);
	ft_putstr(temp);
	ft_memset(temp, ' ', j + (*i)[2]);
	ft_putstr(temp);
	ft_memset(temp, '\b', j + (*i)[2]);
	ft_putstr(temp);
	display_prompt();
	free(temp);
}

void	maxline(char **line, int **i)
{
	char	*tmp;

	(*line)[ft_strlen(*line) - 1] = 0;
	ft_putchar('\b');
	(*i)[2]--;
	(*i)[4]--;
	ft_putstr(ERR_COL);
	ft_putstr("\nminishell: ");
	ft_putstr(DEFAULT_COL);
	ft_putstr("Buffer at max capacity. ");
	ft_putstr("Press Enter to continue...\n");
	tmp = (char *)ft_memalloc(6);
	(*i)[1] = 1;
	while ((*i)[1] == 1)
	{
		read(0, tmp, 6);
		if (tmp[0] == 10)
			(*i)[1] = 0;
	}
	free(tmp);
}

void	handbackslash(char **s)
{
	size_t i;

	i = 0;
	while ((*s)[i] && (*s)[i + 1])
	{
		if ((*s)[i] == '\\' && (*s)[i + 1] != '\\')
			ssupprchr(s, i);
		else if ((*s)[i] == '\\' && (*s)[i + 1] == '\\')
		{
			if ((*s)[i + 2] == ';')
			{
				ssupprchr(s, i);
				ssupprchr(s, i + 1);
			}
			else
				ssupprchr(s, i);
		}
		i++;
	}
}
