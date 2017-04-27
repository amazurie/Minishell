/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 13:37:22 by amazurie          #+#    #+#             */
/*   Updated: 2017/04/27 13:37:32 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			handbackslash(char **s)
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
	while (s[j] == ';' || s[j] == ' ' || s[j] == '\t')
		j++;
	if (!s)
		return (NULL);
	if (!(stab = (char **)ft_memalloc(sizeof(char **) * ft_wds((char *)s))))
		return (NULL);
	stab = ft_split((s + j), stab);
	return (stab);
}

char			**parse_dollar(char *s)
{
	char	**stab;
	char	**tmp;
	size_t	i;
	size_t	j;

	stab = splitsemicolon(s);
	i = 0;
	while (stab[i])
	{
		while ((j = ft_strlen_chr(stab[i], '$')))
		{
			if (stab[i][j + 1] != '$')
				while (stab[i][j] && stab[i][j] != '$')
					ssupprchr(&stab[i], j);
		}
		i++;
	}
	return (stab);
}
