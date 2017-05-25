/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 13:44:01 by amazurie          #+#    #+#             */
/*   Updated: 2017/05/24 17:48:08 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_prompt(void)
{
	int		i;
	char	*pwd;

	if ((pwd = (char *)ft_memalloc(3000)) == NULL)
		return (NULL);
	getcwd(pwd, 2994);
	if (pwd)
	{
		i = ft_strlen(pwd);
		if (i == 1)
			return (pwd);
		while (i > 0 && pwd[i] != '/')
			i--;
	}
	else
		i = -1;
	if (i++ >= 0)
		while (i--)
			ssupprchr(&pwd, 0);
	saddchr(&pwd, '$', 0);
	if (access("./.git", F_OK) != -1)
		ft_strcat(pwd, ": git");
	saddchr(&pwd, '>', ft_strlen(pwd));
	saddchr(&pwd, ' ', ft_strlen(pwd));
	return (pwd);
}

void	display_prompt()
{
	char	*pwd;
	int		i;

	if ((pwd = get_prompt()) == NULL)
			return ;
	ft_putstr_fd(PROMPT_COL, 0);
	if ((i = ft_strschr_len(pwd, "git")) > 0)
	{
		ft_putnstr_fd(pwd, 0, i);
		ft_putstr_fd(PROMPTGIT_COL, 0);
		ft_putnstr_fd((pwd + i), 0, 3);
		ft_putstr_fd(PROMPT_COL, 0);
		ft_putnstr_fd((pwd + i + 3), 0, 3);
	}
	else
		ft_putstr_fd(pwd, 0);
	ft_putstr_fd(DEFAULT_COL, 0);
	free(pwd);
}

void	free_tab(char **tabl)
{
	int i;

	if (!tabl)
		return ;
	i = 0;
	while (tabl[i])
		free(tabl[i++]);
	free(tabl);
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
	char		*path;

	if (!command)
		return (NULL);
	path = ft_strdup(command);
	if (access(path, F_OK) == -1)
		ft_bzero(path, ft_strlen(path));
	return (path);
}
