#include "minishell.h"

static int	get_sline(t_compl *c, int col)
{
	char	*prompt;
	int		i;
	int		j;

	j = 0;
	prompt = get_prompt();
	i = ft_strlen(c->line) + ft_strlen(prompt);
	free(prompt);
	if (c->word)
		i += ft_strlen(c->word);
	while (i > col)
	{
		i -= col;
		j++;
	}
	return (j);
}

int		*get_size(t_compl *c)
{
	struct winsize	w;
	int				*whcl;

	if (!(whcl = (int *)ft_memalloc(sizeof(int) * 9)))
		return (0);
	ioctl(0, TIOCGWINSZ, &w);
	whcl[0] = w.ws_col;
	whcl[1] = w.ws_row - get_sline(c, whcl[0]) - 1;
	whcl[3] = nbrline(c->args, whcl[0], &whcl[2]);
	whcl[4] = nbr_col(c->args, &whcl[3]);
	whcl[5] = check_winsize(c, whcl);
	c->min_line = whcl[5];
	return (whcl);
}

static void	prep_compldisplay(t_compl *c, int *whcl)
{
	t_arg	*ar;
	int		i;

	ft_putstr_fd((c->line + c->i4), 0);
	i = get_sline(c, whcl[0]);
	ft_putstr_fd(tgetstr("do", NULL), 0);
	ft_putstr_fd(tgetstr("up", NULL), 0);
	while (i-- > 0)
		ft_putstr_fd(tgetstr("up", NULL), 0);
	display_prompt();
	ft_putnstr_fd(c->line, 0, c->i4);
	ar = c->args;
	while (ar && ar->num != c->num_curr)
		ar = ar->next;
	if (ar)
		c->word = ar->elem;
	if (c->word)
		ft_putstr_fd(c->word, 0);
	ft_putstr_fd((c->line + c->i4), 0);
	ft_putstr_fd(tgetstr("cd", NULL), 0);
	i = (whcl[4] > whcl[1]) ? whcl[1] : whcl[4];
	while (i-- > 0)
	{
		ft_putstr_fd(tgetstr("do", NULL), 0);
		ft_putstr_fd(tgetstr("dl", NULL), 0);
	}
	i = (whcl[4] > whcl[1]) ? whcl[1] : whcl[4];
	while (i-- > 0)
		ft_putstr_fd(tgetstr("up", NULL), 0);
}

void		display_compl(t_compl *c)
{
	t_arg	*ar;
	int		*whcl;
	int		i;

	ft_putstr_fd(tgetstr("vi", NULL), 0);
	whcl = get_size(c);
	prep_compldisplay(c, whcl);
	whcl[6] = 0;
	whcl[7] = 0;
	ar = c->args;
	while (ar)
	{
		ft_putstr_fd(tgetstr("do", NULL), 0);
		i = whcl[7] * whcl[2];
		while (i-- > 0)
			ft_putstr_fd(tgetstr("nd", NULL), 0);
		if (ar->num == c->num_curr)
			ft_putstr_fd(tgetstr("mr", NULL), 0);
		ft_putstr_fd(ar->elem, 0);
		ft_putstr_fd(tgetstr("me", NULL), 0);
		whcl[6]++;
		ar = ar->next;
		if (whcl[6] == whcl[4] || whcl[6] == whcl[1])
		{
			whcl[7]++;
			while (whcl[6]-- > 0)
				ft_putstr_fd(tgetstr("up", NULL), 0);
			i = whcl[5] + (whcl[4] - (whcl[5] + whcl[1]));
			while (ar && i-- > 0)
				ar = ar->next;
			whcl[6] = 0;
		}
	}
	whcl[6] += get_sline(c, whcl[0]);
	while (whcl[6]-- > 0)
		ft_putstr_fd(tgetstr("up", NULL), 0);
	ft_putstr_fd(tgetstr("do", NULL), 0);
	ft_putstr_fd(tgetstr("up", NULL), 0);
	display_prompt();
	ft_putnstr_fd(c->line, 0, c->i4);
	if (c->word)
		ft_putstr_fd(c->word, 0);
	ft_putstr_fd(tgetstr("ve", NULL), 0);
	free(whcl);
}
