#include "minishell.h"

void	print_line(t_compl *c, char *arg, int *whcl, int **i)
{
	int	j;
	int	k;

	display_prompt();
	ft_putstr_fd(c->line, 0);
	j = ft_strlen(c->line) + ft_strlen(get_prompt());
	if (j > whcl[0])
	{
		while (j > whcl[0])
		{
			j -=whcl[0];
			ft_putstr_fd(tgetstr("up", NULL), 0);
		}
		ft_putnstr_fd(c->line, 0, (*i)[4]);
	}
}

static void	reline(t_compl *c, char *arg, int *whcl, int **i)
{
	int j;

	whcl[7]++;
	while (whcl[7]-- >= 0)
		ft_putstr_fd(tgetstr("up", NULL), 0);
	j = ft_strlen(c->line) + ft_strlen(get_prompt());
	if (j > whcl[0])
	{
		while (j > whcl[0])
		{
			j -=whcl[0];
			ft_putstr_fd(tgetstr("up", NULL), 0);
		}
	}
	print_line(c, NULL, whcl, i);
}

void	display_args(t_compl *c, int *whcl, int **i)
{
	t_arg	*ar;
	int		j;

	whcl[6] = 0;
	whcl[7] = 0;
	ar = c->args;
	while (ar)
	{
		ft_putstr_fd(tgetstr("do", NULL), 0);
		j = whcl[7] * whcl[2];
		while (j-- > 0)
			ft_putstr_fd(tgetstr("nd", NULL), 0);
		ar->pos_x = whcl[6];
		ar->pos_y = whcl[7] * whcl[2];
		if (ar->num == c->num_curr)
			ft_putstr_fd(tgetstr("mr", NULL), 0);
		ft_putstr_fd(ar->elem, 0);
		ft_putstr_fd(tgetstr("me", NULL), 0);
		j = whcl[2] - ft_strlen(ar->elem);
		while (j-- > 0)
			ft_putstr_fd(tgetstr("nd", NULL), 0);
		whcl[6]++;
		ar = ar->next;
		if (whcl[6] == whcl[4] || whcl[6] == whcl[1])
		{
			whcl[7]++;
			j = (whcl[4] > whcl[1]) ? whcl[1] : whcl[4];
			while (j-- > 0)
				ft_putstr_fd(tgetstr("up", NULL), 0);
			j = whcl[5] + (whcl[4] - (whcl[5] + whcl[1]));
			while (ar && j-- > 0)
				ar = ar->next;
			whcl[6] = 0;
		}
	}
	ft_putstr_fd(tgetstr("do", NULL), 0);
	whcl[7] = whcl[6] - 1;
	reline(c, NULL, whcl, i);
}
