/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 13:44:01 by amazurie          #+#    #+#             */
/*   Updated: 2017/03/23 12:06:49 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	display_prompt((*d)->prompt);
	free(temp);
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

char	*get_prompt(char *pwd)
{
	int		i;

	if (pwd)
	{
		i = ft_strlen(pwd);
		while (i > 0 && pwd[i] != '/')
			i--;
	}
	else
		i = 0;
	if (i)
		return ((pwd + i + 1));
	return ("@?");
}

void	display_prompt(char *pwd)
{
	ft_putstr(PROMPT_COL);
	ft_putstr("$");
	ft_putstr(pwd);
	ft_putstr("> ");
	ft_putstr(DEFAULT_COL);
}

void	free_tab(char **tab)
{
	int i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

int		test_paths(char **path)
{
	int	i;

	if (!path || !*path)
		return (0);
	i = 0;
	while (path[i])
		if (access(path[i++], F_OK) == 0)
			return (i);
	return (0);
}

char	*test_absolute(char *command)
{
	struct stat	atr;
	char		*path;
	char		tmp[4096];
	char		*tmp2;
	int			i;

	if (!command)
		return (NULL);
	ft_bzero(tmp, 4096);
	path = ft_strjoin(tmp, command);
	if (stat(command, &atr) == 0)
		getcwd(tmp, 4095);
	tmp2 = ft_strjoin(tmp, "/");
	if (ft_strncmp(command, "./", 2) == 0)
	{
		ssupprchr(&command, 0);
		ssupprchr(&command, 0);
	}
	path = ft_strjoin(tmp2, command);
	if (access(path, F_OK) == -1)
		ft_bzero(path, ft_strlen(path));
	free(tmp2);
	return (path);
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
