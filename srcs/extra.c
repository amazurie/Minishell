/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 11:57:35 by amazurie          #+#    #+#             */
/*   Updated: 2017/03/03 16:36:03 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ssupprchr(char **s, int pos)
{
	int i;

	pos--;
	i = ft_strlen(*s) - 1;
	while (++pos <= i)
		(*s)[pos] = (*s)[pos + 1];
}

void			saddchr(char **s, char c, int pos)
{
	int i;

	i = ft_strlen(*s) + 1;
	while (--i >= pos)
		(*s)[i + 1] = (*s)[i];
	(*s)[pos] = c;
}

static size_t	ft_wds(char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == ';')
			i++;
		while (str[i] == ';' && str[i - 1] != '\\')
			i++;
		if (str[i] && (str[i] != ';' ||
					(str[i] == ';' && str[i - 1] == '\\')))
			j++;
		while (str[i] && (str[i] != ';' ||
					(str[i] == ';' && str[i - 1] == '\\')))
			i++;
	}
	return (j + 1);
}

static char		**ft_split(char const *s, char **stab)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;

	i = 0;
	k = 0;
	while (s[i])
	{
		j = 0;
		if (s[i] != ';' || (i > 0 && s[i] == ';' && s[i - 1] == '\\'))
		{
			while (s[i + j] && (s[i + j] != ';' || (s[i + j] == ';'
						&& s[i + j - 1] == '\\')))
				j++;
			stab[k++] = ft_strsub(s, i, j);
			i += j;
		}
		else
			while (s[i] && i > 0 && s[i] == ';' && s[i - 1] != '\\')
				i++;
		stab[k] = NULL;
	}
	return (stab);
}

char			**splitsemicolon(char *s)
{
	char	**stab;
	size_t	j;

	j = 0;
	while (s[j] == ';' || s[j] == ' ')
		j++;
	if (!s)
		return (NULL);
	if (!(stab = (char **)ft_memalloc(sizeof(char **) * ft_wds((char *)s))))
		return (NULL);
	stab = ft_split((s + j), stab);
	return (stab);
}
