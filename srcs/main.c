/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 12:41:32 by amazurie          #+#    #+#             */
/*   Updated: 2017/03/03 17:13:57 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static struct termios old, new;

char		get_ch()
{
	char *ch;
	ch = (char*)ft_memalloc(2);
	tcgetattr(0, &old);
	new = old;
	new.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(0, TCSANOW, &new);
	while (ch[0] == 0 && SIGINTED != 1)
		read(0, ch, 1);
	tcsetattr(0, TCSANOW, &old);
	return (ch[0]);
}

int		check(char tmp, h_list *hist)
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

void		sighandler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr("\n\e[1;36m$> \e[0m");
		SIGINTED = 1;
	}
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
		tmp = get_ch();
		if (SIGINTED == 1)
		{
			ft_memset(*line, 0, i[2]);
			i[2] = 0;
			i[3] = -1;
			i[4] = 0;
			SIGINTED = 0;
		}
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
			i[1] = ++i[2];
			while (--i[1] > i[4])
				ft_putchar('\b');
			i[4]++;
		}
		else if (i[0] == 3 && i[4] > 0)
		{
			ft_putchar('\b');
			ft_putstr(((*line) + i[4]));
			ft_putstr(" \b");
			ssupprchr(line, --i[4]);
			i[1] = i[2];
			while (--i[1] > i[4])
				ft_putchar('\b');
			i[2]--;
		}
		else if (i[0] == 2)
			gest_arrow(tmp, hist, &i, line);
	}
	return (1);
}

int			main(int ac, char **av, char **env)
{
	e_list	*e;
	h_list	*hist;
	char	**lstline;
	char	*line;
	int		i;

	//remove last output character
	//printf("\b");
	e = char_to_lst(env);
	hist = NULL;
	while (42)
	{
		signal(SIGINT, sighandler);
		if (SIGINTED == 0)
			ft_putstr("\e[1;36m$> \e[0m");
		SIGINTED = 0;
		if ((i = in(hist, &line)) == -1)
			return (0);
		ft_putchar('\n');
		if (i == 1)
		{
			if (*line && (hist == NULL || ft_strcmp(hist->hist, line) != 0))
				add_hist(&hist, line);
			lstline = splitsemicolon(line);
			i = 0;
			while (lstline[i++])
				if (lstline[i - 1] != NULL && exec(e, lstline[i - 1], hist) == -1)
					return (0);
		}
	}
	return (0);
}
