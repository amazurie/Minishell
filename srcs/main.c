/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 12:41:32 by amazurie          #+#    #+#             */
/*   Updated: 2017/04/25 17:52:40 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		sighandler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 0);
		display_prompt();
		is_siginted(1);
	}
	if (sig == SIGSTOP)
	{
		while (0)
			;
	}
}

static int	in(t_data **d, char *tmp)
{
	int		*i;
	int		j;

	is_siginted(1);
	i = (int *)ft_memalloc(sizeof(int) * 6);
	if (read(0, tmp, 0) == -1)
		return (-1);
	while (i[0] == 0)
	{
		read(0, tmp, 5);
		if (is_siginted(0) == 1)
		{
			ft_memset((*d)->line, 0, i[2]);
			i[2] = 0;
			i[3] = -1;
			i[5] = 0;
			i[4] = 0;
		}
		if (gest_in(d, tmp, &i) == -1)
			i[0] = -1;
		ft_bzero(tmp, 6);
	}
	j = i[0];
	free(i);
	return (j);
}

static int	hand_arg(char *line, t_hist **hist, t_env **env)
{
	char	**lstline;
	size_t	i;
	int		j;

	j = 1;
	if (*line && (*hist == NULL || ft_strcmp((*hist)->hist, line) != 0))
		add_hist(hist, line);
	lstline = splitsemicolon(line);
	i = 0;
	while (lstline[i++])
		if (lstline[i - 1] != NULL &&
				exec(env, lstline[i - 1], *hist) == -1)
			j = 0;
	i = 0;
	while (lstline[i])
		free(lstline[i++]);
	free(lstline);
	return (j);
}

static void	shell(t_data **d)
{
	char	*tmp;
	int		i[2];

	(*d)->hist = NULL;
	i[0] = 1;
	while (i[0] == 1)
	{
		(*d)->prompt = get_prompt();
		if (!is_siginted(0))
			display_prompt();
		tmp = (char *)ft_memalloc(6);
		if ((i[1] = in(d, tmp)) == -1)
			i[0] = 0;
		free(tmp);
		ft_putchar_fd('\n', 0);
		if (i[1] == 1 && i[0] == 1)
			i[0] = hand_arg((*d)->line, &((*d)->hist), &((*d)->env));
		ft_bzero((*d)->line, ft_strlen((*d)->line));
		if ((*d)->prompt)
			free((*d)->prompt);
	}
}

int			main(int ac, char **av, char **env)
{
	static struct termios	old;
	static struct termios	new;
	t_data					*d;

	tcgetattr(0, &old);
	new = old;
	new.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(0, TCSANOW, &new);
	signal(SIGINT, sighandler);
	d = (t_data *)ft_memalloc(sizeof(t_data));
	d->env = char_to_lst(env);
	d->line = (char *)ft_memalloc(2048);
	d->buffline = (char *)ft_memalloc(2048);
	shell(&d);
	if (d->hist != NULL)
		del_hist(d->hist);
	tcsetattr(0, TCSANOW, &old);
	free(d->buffline);
	free(d->line);
	free(d);
	av[0][0] = ac;
	return (0);
}
