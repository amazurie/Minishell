/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 12:41:32 by amazurie          #+#    #+#             */
/*   Updated: 2017/03/15 13:37:25 by amazurie         ###   ########.fr       */
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
		ft_putchar('\n');
		display_prompt(PROMPT);
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
	int		j;

	tcgetattr(0, &old);
	new = old;
	new.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(0, TCSANOW, &new);
	//signal(SIGINT, sighandler);
	e = char_to_lst(env);
	hist = NULL;
	i = 1;
	while (i == 1)
	{
		PROMPT = get_elem(e, "PWD");
		if (SIGINTED == 0)
			display_prompt(get_elem(e, "PWD"));
		SIGINTED = 0;
		SIGSTOPED = 0;
		if ((j = in(hist, &line)) == -1)
			i = 0;
		ft_putchar('\n');
		if (j == 1 && i == 1)
		{
			if (*line && (hist == NULL || ft_strcmp(hist->hist, line) != 0))
				add_hist(&hist, line);
			lstline = splitsemicolon(line);
			j = 0;
			while (lstline[j++])
				if (lstline[j - 1] != NULL &&
						exec(e, lstline[j - 1], hist) == -1)
					i = 0;
			j = 0;
			while (lstline[j])
				free(lstline[j++]);
			free(lstline);
		}
		free(line);
	}
	if (hist != NULL)
		del_hist(hist);
	tcsetattr(0, TCSANOW, &old);
	return (0);
}
