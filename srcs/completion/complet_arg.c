/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complet_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 11:29:42 by amazurie          #+#    #+#             */
/*   Updated: 2017/06/20 14:55:22 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_command(t_data **d, int **i)
{
	int		j;

	if ((*i)[4] == 0)
		return (0);
	j = (*i)[4] - 1;
	while (j > (*i)[6] && (*d)->line[j] != 32 && (*d)->line[j] != 34
			&& (*d)->line[j] != 96)
		j--;
	if (j == (*i)[6])
		return (0);
	while (j > (*i)[6] && ((*d)->line[j] == 32 || (*d)->line[j] == 34
				|| (*d)->line[j] == 96))
		j--;
	if ((*d)->line[j] == 32)
		return (0);
	return (1);
}

int		check_quotecompl(t_data **d, int **i)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while ((*d)->line[k] && k <= (*i)[4])
	{
		if ((*d)->line[k] == 34 && j != 2)
		{
			if (j == 0)
				j = 1;
			else
				j = 0;
		}
		else if ((*d)->line[k] == 39 && j != 1)
		{
			if (j == 0)
				j = 2;
			else
				j = 0;
		}
		k++;
	}
	return (j);
}

static void	check_home(t_data **d, char **word)
{
	char	*tmp;
	char	*tmp2;

	if (ft_strcmp(*word, "~") == 0)
	{
		ft_bzero(*word, ft_strlen(*word));
		ft_strcat(*word, get_elem((*d)->env, "HOME"));
	}
	else if ((*word)[0] == '~' && (*word)[1] == '/')
	{
		tmp = ft_strdup(*word + 1);
		ft_bzero(*word, ft_strlen(*word));
		tmp2 = get_elem((*d)->env, "HOME");
		if (!tmp2)
			tmp = "~";
		ft_strcat(*word, tmp2);
		ft_strcat(*word, tmp);
		free(tmp);
	}
}

char	*recover_wtocompl(t_data **d, int **i)
{
	char	*word;
	int		j;
	int		k;

	k = 0;
	if (check_quotecompl(d, i))
		k = 1;
	if (!(word = (char *)ft_memalloc(301)))
		return (NULL);
	j = (*i)[4] - 1;
	while (j > (*i)[6] && ((k == 1 && ((*d)->line[j] != '"'
			|| (*d)->line[j] != '\'')) || (k == 0 && (*d)->line[j] != ' ')))
		j--;
	while ((*d)->line[j] == ' ')
		j++;
	if (j > (*i)[4] || (*i)[4] - j > 300)
		return (NULL);
	ft_strncat(word, ((*d)->line + j), (*i)[4] - j);
	check_home(d, &word);
	return (word);
}

void	free_complargs(t_arg *arg)
{
	t_arg	*ar;

	if (arg == NULL)
		return ;
	while (arg->next)
	{
		ar = arg;
		arg = arg->next;
		free(ar->elem);
		free(ar);
	}
	free(arg->elem);
	free(arg);
}
