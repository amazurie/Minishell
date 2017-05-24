/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 13:37:22 by amazurie          #+#    #+#             */
/*   Updated: 2017/05/24 19:04:29 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		handbackslash(char **s)
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
		while (str[i] == ';')
			i++;
		if (str[i] && str[i] != ';')
			j++;
		while (str[i] && str[i] != ';')
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
		if (s[i] != ';')
		{
			while (s[i] && s[i] == ' ')
				i++;
			while (s[i + j] && s[i + j] != ';')
				j++;
			stab[k++] = ft_strsub(s, i, j);
			i += j;
		}
		else
			while (s[i] && s[i] == ';')
				i++;
		stab[k] = NULL;
	}
	return (stab);
}

static char		**splitsemicolon(char *s)
{
	char	**stab;
	size_t	j;

	j = 0;
	while (s[j] == ';' || s[j] == ' ' || s[j] == '\t')
		j++;
	if (!s)
		return (NULL);
	if (!(stab = (char **)ft_memalloc(sizeof(char *) * ft_wds(s) + 1)))
		return (NULL);
	stab = ft_split((s + j), stab);
	return (stab);
}

char			**parse_dollar(char *s)
{
	char	**stab;
	size_t	i;
	size_t	j;

	handbackslash(&s);
	if ((stab = splitsemicolon(s)) == NULL)
		return (NULL);
/*	i = 0;
	while (stab[i])
	{
		while ((j = ft_strlen_chr(stab[i], '$')) < ft_strlen(stab[i]) - 1)
		{
			if (stab[i][j + 1] != '$')
				while (stab[i][j] && stab[i][j] != '$')
					ssupprchr(&stab[i], j);
		}
		i++;
	}
*/	return (stab);
}
