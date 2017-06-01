#include "minishell.h"

int		do_setup(t_data **d, t_compl *c, char *word, int **i)
{
	t_arg	*args;
	int	j;

	if (!(c->args = list_arg(d, c, i, word)))
		return (0);
	c->line = ft_strdup((*d)->line);
	j = 0;
	if (word)
		j = ft_strlen(word);
	c->i4 = (*i)[4] - j;
	while (j-- > 0)
	{
		ssupprchr(&(c->line), c->i4);
		curs_left(d, i);
	}
	args = c->args;
	j = 0;
	while (args)
	{
		args->num = j;
		args = args->next;
		j++;
	}
	c->ac = j - 1;
	return (1);
}

void	insert_word(t_data **d, t_compl *c, char *word, int **i)
{
	if (c->ac != -1)
	{
		c->ac = 0;
		if (c->word)
			c->ac = ft_strlen(c->word);
		if (word)
			c->ac -= ft_strlen(word);
		while (c->ac-- > 0)
			curs_left(d, i);
		c->ac = 0;
		if (word)
			c->ac = ft_strlen(word);
		if (c->word)
			chr_in(d, (c->word + c->ac), i);
	}
	free_complargs(c->args);
	if (word)
		free(word);
	if (c->line)
		free(c->line);
}

int		compl_star(t_data **d, t_compl *c, char *word, int **i)
{
	t_arg	*ar;
	char	*tmp;
	char	*tmp2;

	if (c->is_star == 0)
		return (0);
	ssupprchr(&((*d)->line), (*i)[4] - 1);
	curs_left(d, i);
	(*i)[4]--;
	(*i)[2]--;
	ar = c->args;
	tmp = ft_strjoin(ar->elem, " ");
	ar = ar->next;
	while (ar->next)
	{
		tmp2 = ft_strjoin(tmp, ar->elem);
		free(tmp);
		tmp = ft_strjoin(tmp2, " ");
		free(tmp2);
		ar = ar->next;
	}
	chr_in(d, tmp, i);
	c->word = ar->elem;
	free(tmp);
	return (1);
}

int		completion(t_data **d, char **tmp, int **i)
{
	t_compl	c;
	char	*word;
	int		j;

	if ((*tmp)[0] != 9 || (*tmp)[1] || (*i)[6] > 0)
		return (0);
	while ((*i)[4] < (*i)[2] && (*d)->line[(*i)[4]] != '"'
			&& (*d)->line[(*i)[4]] != '\'' && (*d)->line[(*i)[4]] != ' ')
	{
		curs_right(d, i);
		(*i)[4]++;
	}
	word = recover_wtocompl(d, i);
	if (do_setup(d, &c, word, i) == 0)
		return (0);
	c.word = word;
	c.min_line = 0;
	if ((j = compl_star(d, &c, word, i)) == 0)
		j = complet_arg(&c, tmp);
	if (j == -1)
		c.ac = -1;
	insert_word(d, &c, word, i);
	if (j == -1)
		return (0);
	return (j);
}
