#include "minishell.h"

void	print_line(t_compl *c, char *word, int col, int **i)
{
	int	j;
	int	k;

	display_prompt();
	j = 0;
	if (word)
	{
		ft_putnstr_fd(c->line, 0, (*i)[4]);
		ft_putstr_fd(word, 0);
		ft_putstr_fd((c->line + (*i)[4]), 0);
		j = ft_strlen(word);
	}
	else
		ft_putstr_fd(c->line, 0);
	ft_putstr_fd(tgetstr("ce", NULL), 0);
	j += ft_strlen(c->line) + ft_strlen(get_prompt());
	if (col && j > col)
	{
		while (j > col)
		{
			j -= col;
			ft_putstr_fd(tgetstr("up", NULL), 0);
		}
		ft_putnstr_fd(c->line, 0, (*i)[4]);
	}
}

static void	reline(t_compl *c, char *word, int *whcl, int **i)
{
	int j;

	while (whcl[6]-- >= 0)
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
	print_line(c, word, whcl[0], i);
}

int	*get_size(t_compl *c)
{
	struct winsize	w;
	int				*whcl;

	if (!(whcl = (int *)ft_memalloc(sizeof(int) * 9)))
		return (0);
	ioctl(0, TIOCGWINSZ, &w);
	whcl[0] = w.ws_col;
	whcl[1] = w.ws_row - 1;
	whcl[3] = nbrline(c->args, whcl[0], &whcl[2]);
	whcl[4] = nbr_col(c->args, &whcl[3]);
	whcl[5] = check_winsize(c, whcl);
	c->min_line = whcl[5];
	return (whcl);
}

void	display_compl(t_compl *c, int **i)
{
	char	*word;
	int		*whcl;
	t_arg	*ar;
	int		j;

	word = c->word;
	whcl = get_size(c);
	whcl[6] = 0;
	whcl[7] = 0;
	ar = c->args;
	ft_putstr_fd(tgetstr("vi", NULL), 0);
	j = whcl[5];
	while (ar && j-- > 0)
		ar = ar->next;
	j = whcl[5] + (whcl[4] - (whcl[5] + whcl[1]));
	while (j-- > 0)
	{
		ft_putstr_fd(tgetstr("do", NULL), 0);
		ft_putstr_fd(tgetstr("dl", NULL), 0);
	}
	j = whcl[5] + (whcl[4] - (whcl[5] + whcl[1]));
	while (j-- > 0)
		ft_putstr_fd(tgetstr("up", NULL), 0);
	while (ar)
	{
		ft_putstr_fd(tgetstr("do", NULL), 0);
		j = whcl[7] * whcl[2];
		while (j-- > 0)
			ft_putstr_fd(tgetstr("nd", NULL), 0);
		if (ar->num == c->num_curr)
			word = ar->elem;
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
	reline(c, word, whcl, i);
	free(whcl);
	ft_putstr_fd(tgetstr("ve", NULL), 0);
}
