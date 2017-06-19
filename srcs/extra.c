/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 12:42:53 by amazurie          #+#    #+#             */
/*   Updated: 2017/06/19 11:20:03 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ssupprchr(char **s, int pos)
{
	int i;

	pos--;
	i = ft_strlen(*s) - 1;
	while (++pos <= i)
		(*s)[pos] = (*s)[pos + 1];
}

void	saddchr(char **s, char c, int pos)
{
	int i;

	i = ft_strlen(*s) + 1;
	while (--i >= pos)
		(*s)[i + 1] = (*s)[i];
	(*s)[pos] = c;
}

void	erase_printline(t_data **d, int **i)
{
	struct winsize	w;
	int				j;
	int				k;

	(*i)[1] = 0;
	j = ft_strlen((*d)->prompt) + (*i)[4] - (*i)[6];
	ioctl(0, TIOCGWINSZ, &w);
	if (w.ws_col * w.ws_row <= ft_strlen((*d)->prompt) + (*i)[2])
	{
		ft_putstr_fd(tgoto(tgetstr("cm", NULL), 0, 0), 0);
		j = 0;
	}
	k = (*i)[4];
	while (--j > 0)
	{
		curs_left(d, i);
		(*i)[4]--;
	}
	(*i)[4] = k;
	ft_putstr_fd(tgetstr("cd", NULL), 0);
	ft_putstr_fd(tgetstr("le", NULL), 0);
	if ((*i)[6] == 0)
		display_prompt();
	else
		ft_putstr_fd((*d)->prompt, 0);
}

void	maxline(t_data **d, char *tmp, int **i)
{
	if ((*i)[4] == (*i)[2])
		((*d)->line)[(*i)[4] - 1] = tmp[0];
	else
		((*d)->line)[(*i)[4]] = tmp[0];
	ft_putstr_fd(tgetstr("cr", NULL), 0);
	ft_putstr_fd(tgetstr("cd", NULL), 0);
	if ((*i)[6] == 0)
		display_prompt();
	else
		ft_putstr_fd((*d)->prompt, 0);
	ft_putstr_fd(((*d)->line + (*i)[6]), 0);
	ft_putstr_fd(ERR_COL, 2);
	ft_putstr_fd("\nminishell: ", 2);
	ft_putstr_fd(DEFAULT_COL, 2);
	ft_putstr_fd("Buffer at max capacity.\n", 2);
	display_prompt();
	if ((*i)[6] == 0)
		ft_putstr_fd((*d)->line, 0);
	(*i)[4] = (*i)[2];
	if ((*i)[6] == 0)
		return ;
	ft_putnstr_fd((*d)->line, 0, (*i)[6]);
	ft_putchar_fd('\n', 0);
	ft_putstr_fd((*d)->prompt, 0);
	ft_putstr_fd(((*d)->line + (*i)[6]), 0);
}

char	**lst_to_char(t_env *env)
{
	char	**lstenv;
	t_env	*tmp;
	char	*buff;
	int		i;

	i = 0;
	tmp = env;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	if ((lstenv = (char **)ft_memalloc(sizeof(char *) * (i + 1))) == NULL)
		return (NULL);
	tmp = env;
	i = 0;
	while (tmp)
	{
		buff = ft_strjoin(tmp->elem, "=");
		lstenv[i] = ft_strjoin(buff, tmp->cont);
		free(buff);
		tmp = tmp->next;
		i++;
	}
	return (lstenv);
}
