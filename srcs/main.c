/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 12:41:32 by amazurie          #+#    #+#             */
/*   Updated: 2017/03/08 17:23:34 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static struct termios old;
static struct termios new;

void		sighandler(int sig)
{

	SIGSTOPED = 1;
	if (sig == SIGINT)
	{
		ft_putstr("\n\e[1;36m$> \e[0m");
		SIGINTED = 1;
	}
	if (sig == SIGSTOP)
	{
		while (SIGSTOPED == 0)
			;
	}
}

int			main(int ac, char **av, char **env)
{
	e_list	*e;
	h_list	*hist;
	char	**lstline;
	char	*line;
	int		i;

	tcgetattr(0, &old);
	new = old;
	new.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(0, TCSANOW, &new);
	e = char_to_lst(env);
	hist = NULL;
	while (42)
	{
		//signal(SIGINT, sighandler);
		if (SIGINTED == 0)
			ft_putstr("\e[1;36m$> \e[0m");
		SIGINTED = 0;
		SIGSTOPED = 0;
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
				if (lstline[i - 1] != NULL &&
						exec(e, lstline[i - 1], hist) == -1)
					return (0);
		}
	}
	tcsetattr(0, TCSANOW, &old);
	return (0);
}
