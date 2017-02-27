/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 12:41:32 by amazurie          #+#    #+#             */
/*   Updated: 2017/02/27 17:07:30 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static struct termios old, new;

char getch()
{
	char *ch;
	ch = (char*)ft_memalloc(2);
	tcgetattr(0, &old);
	new = old;
	new.c_lflag &= ~(ECHO|ICANON);
	tcsetattr(0, TCSANOW, &new);
	while (read(0, ch, 1) == 0)
		;
	tcsetattr(0, TCSANOW, &old);
	return (ch[0]);
}

int	check(char *tmp, h_list *hist)
{
	if (tmp[0] == 27)
	{
		/*tmp[1] = getch();
		tmp[2] = getch();
		//if (tmp[2] == 65)
		//	printf("\nfleche haut\n");
		if (tmp[2] == 66)
			printf("\nfleche bas\n");
		if (tmp[2] == 67)
			printf("\nfleche droite\n");
		if (tmp[2] == 68)
			printf("\nfleche gauche\n");
		*/return (2);
	}
	else if (tmp[0] == 127)
		return (3);
	else if (tmp[0] == 10)
		return (1);
	else if (tmp[0] == 4)
		return (-1);
	return (0);
}

static int	gest_arrow(char *tmp, h_list *hist, int *histnum, char **line)
{
	int	i;

	tmp[0] = getch();
	tmp[0] = getch();
	if (tmp[0] == 67 || tmp[0] == 68)
	{
		tmp[0] = 0;
		return ft_strlen(*line);
	}
	tmp[0] = 0;
	i = ft_strlen(*line);
	ft_memset(*line, '\b', i);
	ft_putstr(*line);
	ft_memset(*line, ' ', i);
	ft_putstr(*line);
	ft_memset(*line, '\b', i);
	ft_putstr(*line);
	ft_memset(*line, 0, i);
	i = ft_strlen(*line);
	return (0);
}

static int	in(h_list *hist, char **line)
{
	char	*tmp;
	int		i[4];
	int		histnum;

	*line = (char *)ft_memalloc(256);
	tmp = (char *)ft_memalloc(5);
	i[0] = 0;
	i[2] = 0;
	histnum = 0;
	while (i[0] != 1)
	{
		tmp[0] = getch();
		//printf("\nYou typed: %i\n", tmp[0]);
		if ((i[0] = check(tmp, hist)) == -1)
			return (-1);
		else if (i[0] == 0)
		{
			ft_putchar(tmp[0]);
			i[1] = 0;
			while (tmp[i[1]])
				(*line)[i[2]++] = tmp[i[1]++];
		}
		else if (i[0] == 3 && i[2] > 0)
		{
			ft_putstr("\b \b");
			(*line)[--i[2]] = 0;
		}
		if (i[0] == 2)
			i[2] = gest_arrow(tmp, hist, &histnum, line);
	}
	free(tmp);
	return (0);
}

int			main(int ac, char **av, char **env)
{
	e_list	*e;
	h_list	*hist;
	char	*line;

	//remove last output character
	//printf("\b");
	e = char_to_lst(env);
	hist = NULL;
	while (42)
	{
		ft_putstr("\e[1;36m$> \e[0m");
		if (in(hist, &line) == -1)
			return (0);
		ft_putchar('\n');
		if (*line && ft_strcmp(line, "history") != 0)
			add_hist(&hist, line);
		if (*line && exec(e, line, hist) == -1)
			return (0);
	}
	return (0);
}
