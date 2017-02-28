/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 12:41:32 by amazurie          #+#    #+#             */
/*   Updated: 2017/02/28 14:39:43 by amazurie         ###   ########.fr       */
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

int	check(char tmp, h_list *hist)
{
	if (tmp == 27)
		return (2);
	else if (tmp == 127)
		return (3);
	else if (tmp == 10)
		return (1);
	else if (tmp == 4)
		return (-1);
	return (0);
}

static int	gest_arrow(char tmp, h_list *hist, int **i, char **line)
{
	int	j;

	tmp = getch();
	tmp = getch();
	if (tmp == 67 || tmp == 68)
	{
		if ((*i)[4] > 0 && tmp == 68)
		{
			ft_putchar('\b');
			tmp = 0;
			(*i)[4]--;
		}
		else if ((*i)[4] < (*i)[2] && tmp == 67)
		{
			ft_putchar((*line)[(*i)[4]]);
			tmp = 0;
			(*i)[4]++;
		}
		return 0;
	}
	j = ft_strlen(*line);
	ft_memset(*line, '\b', j);
	ft_putstr(*line);
	ft_memset(*line, ' ', j);
	ft_putstr(*line);
	ft_memset(*line, '\b', j);
	ft_putstr(*line);
	ft_memset(*line, 0, j);
	if (tmp == 65)
	{
		if ((j = disp_hist_next(hist, i, line)) != -1)
		{
			(*i)[2] = j;
			(*i)[4] = j;
		}
		else
			(*i)[4] = 0;
	}
	if (tmp == 66)
	{
		if ((j = disp_hist_prec(hist, i, line)) != -1)
		{
			(*i)[2] = j;
			(*i)[4] = j;
		}
		else
			(*i)[4] = 0;
	}
	tmp = 0;
	return (0);
}

void sighandler(int sig)
{
	if (sig == SIGABRT)
		exit(1);
}

static int	in(h_list *hist, char **line)
{
	char	tmp;
	int		*i;

	*line = (char *)ft_memalloc(256);
	i = (int *)ft_memalloc(sizeof(int) * 5);
	i[3] = -1;
	while (i[0] != 1)
	{
		tmp = getch();
		//printf("\ntyped: %i\n", tmp);
		if ((i[0] = check(tmp, hist)) == -1)
			return (-1);
		else if (i[0] == 0)
		{
			i[1] = 0;
			while (i[1]++ < i[4])
				ft_putchar('\b');
			saddchr(line, tmp, i[4]);
			ft_putstr(*line);
			ft_putstr(" \b");
			i[1] = ft_strlen(*line);
			while (--i[1] > i[4])
				ft_putchar('\b');
			i[2]++;
			i[4]++;
		}
		else if (i[0] == 3 && i[4] > 0)
		{
			ft_putchar('\b');
			ft_putstr(((*line) + i[4]));
			ft_putstr(" \b");
			ssupprchr(line, --i[4]);
			i[2]--;
		}
		if (i[0] == 2)
			gest_arrow(tmp, hist, &i, line);
	}
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
		signal(SIGINT, sighandler);
		ft_putstr("\e[1;36m$> \e[0m");
		if (in(hist, &line) == -1)
			return (0);
		ft_putchar('\n');
		if (*line && (hist == NULL || ft_strcmp(hist->hist, line) != 0))
			add_hist(&hist, line);
		if (*line && exec(e, line, hist) == -1)
			return (0);
	}
	return (0);
}
