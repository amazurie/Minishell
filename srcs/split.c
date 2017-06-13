/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 13:37:22 by amazurie          #+#    #+#             */
/*   Updated: 2017/06/13 09:09:31 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		handbackslash(char **s)
{
	int	i;

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
	int	i;
	int	j;

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

static int		split(char **s, int *i)
{
	int	j;

	j = 0;
	while ((*s)[*i + j] && (*s)[*i + j] != ';' && ++j >= 0)
	{
		if ((*s)[*i + j] && (*s)[*i + j] == '"')
		{
			ssupprchr(s, *i + j);
			while ((*s)[*i + j] && (*s)[*i + j] != '"')
				j++;
			if ((*s)[*i + j])
				ssupprchr(s, *i + j);
			j--;
		}
		else if ((*s)[*i + j] && (*s)[*i + j] == '\'')
		{
			ssupprchr(s, *i + j);
			while ((*s)[*i + j] && (*s)[*i + j] != '\'')
				j++;
			if ((*s)[*i + j])
				ssupprchr(s, *i + j);
			j--;
		}
	}
	return (j);
}

static char		**ft_split(char *s, char **stab)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (s[i])
	{
		if (s[i] != ';')
		{
			while (s[i] && s[i] == ' ')
				i++;
			j = split(&s, &i);
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

char			**splitsemicolon(char *s)
{
	char	**stab;
	int		j;

	handbackslash(&s);
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
