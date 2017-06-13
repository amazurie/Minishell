/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 12:41:32 by amazurie          #+#    #+#             */
/*   Updated: 2017/06/13 13:44:36 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		sigexec(int sig)
{
	if (sig == SIGINT)
		is_siginted(1);
}

void		sighandler(int sig)
{
	t_data	*d;

	if (sig == SIGINT)
	{
		d = get_data(NULL);
		ft_putstr_fd((d->line + d->i[4]), 0);
		ft_bzero(d->line, ft_strlen(d->line));
		ft_putchar_fd('\n', 0);
		ft_putstr_fd(tgetstr("cd", NULL), 0);
		display_prompt();
		is_siginted(1);
	}
}

static int	hand_arg(char *line, t_hist **hist, t_env **env)
{
	char	**lstline;
	size_t	i;
	int		j;

	j = 1;
	if (*line && (*hist == NULL || ft_strcmp((*hist)->hist, line) != 0))
		add_hist(hist, line);
	if ((lstline = splitsemicolon(line)) == NULL)
		return (print_error("parsing error") + 1);
	i = 0;
	while (lstline[i++])
		if (lstline[i - 1] != NULL && lstline[i - 1][0] &&
				exec(env, lstline[i - 1], *hist) == -1)
			j = 0;
	i = 0;
	while (lstline[i])
		free(lstline[i++]);
	free(lstline);
	ft_putstr_fd(tgetstr("cd", NULL), 0);
	return (j);
}

static int	shell(t_data **d)
{
	char	*tmp;
	int		i[2];

	signal(SIGTSTP, &sighandler);
	(*d)->hist = NULL;
	i[0] = 1;
	while (i[0] == 1)
	{
		if (((*d)->prompt = get_prompt()) == NULL)
			return (print_error("allocation error"));
		display_prompt();
		if ((tmp = (char *)ft_memalloc(LIMIT_LINE)) == NULL)
			return (print_error("allocation error"));
		signal(SIGINT, &sighandler);
		if ((i[1] = in(d, tmp)) == -1)
			i[0] = 0;
		free(tmp);
		signal(SIGINT, &sigexec);
		if (i[1] == 1 && i[0] == 1)
			i[0] = hand_arg((*d)->line, &((*d)->hist), &((*d)->env));
		ft_bzero((*d)->line, ft_strlen((*d)->line));
		if ((*d)->prompt)
			free((*d)->prompt);
	}
	return (1);
}

int			main(int ac, char **av, char **env)
{
	static struct termios	old;
	static struct termios	new;
	char					*name_term;
	t_data					*d;

	if ((d = data_alloc(env)) == NULL)
		return (print_error("allocation error"));
	if (!(name_term = get_elem(d->env, "TERM")) || tgetent(NULL, name_term) < 1)
	{
		data_free(&d);
		if (!name_term)
			return (print_error("No term specified, specify by setting TERM"));
		return (print_error("Can't load TERM entry, make sure to specify it"));
	}
	tcgetattr(0, &old);
	tcgetattr(0, &new);
	new.c_lflag &= ~(ECHO | ICANON);
	new.c_cc[VMIN] = 1;
	new.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &new);
	shell(&d);
	tcsetattr(0, TCSANOW, &old);
	data_free(&d);
	av[0][0] = ac;
	return (0);
}
