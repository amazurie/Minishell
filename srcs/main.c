/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 12:41:32 by amazurie          #+#    #+#             */
/*   Updated: 2017/02/27 14:01:33 by amazurie         ###   ########.fr       */
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
		tmp[1] = getch();
		tmp[2] = getch();
		if (tmp[2] == 65)
			printf("\nfleche haut\n");
		if (tmp[2] == 66)
			printf("\nfleche bas\n");
		if (tmp[2] == 67)
			printf("\nfleche droite\n");
		if (tmp[2] == 68)
			printf("\nfleche gauche\n");
		return (2);
	}
	else if (tmp[0] == 127)
		return (3);
	else if (tmp[0] == 10)
		return (1);
	else if (tmp[0] == 4)
		return (-1);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	e_list	*e;
	h_list	*hist;
	char	*line;
	char	tmp[5];
	int		size;
	int		count;
	int		i;
	int		j;

	//remove last output character
	//printf("\b");
	e = char_to_lst(env);
	hist = NULL;
	while (42)
	{
		ft_putstr("\e[1;36m$> \e[0m");
		line = (char *)ft_memalloc(256);
		//printf("(getch example) please type a letter...");
		i = 0;
		count = 0;
		while (i != 1)
		{
			tmp[0] = getch();
			//printf("\nYou typed: %i\n", tmp[0]);
			if ((i = check(tmp, hist)) == -1)
				return (0);
			else if (i == 0)
			{
				ft_putchar(tmp[0]);
				j = 0;
				while (tmp[j])
					line[count++] = tmp[j++];
					}
			else if (i == 3 && count > 0)
			{
				ft_putstr("\b \b");
				line[--count] = 0;
			}
		}
		hist = add_hist(&hist, line);
		ft_putchar('\n');
		if (*line && exec(e, line) == -1)
			return (0);
		display_hist(&hist);
	}
	return (0);
}
