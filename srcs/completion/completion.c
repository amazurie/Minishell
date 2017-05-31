#include "minishell.h"

void	do_setup(t_data **d, t_compl *c, char *word, int **i)
{
	t_arg	*args;
	int	j;

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
}

void	insert_word(t_data **d, t_compl *c, char *word, int **i)
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

int		completion(t_data **d, char **tmp, int **i)
{
	t_compl	c;
	t_arg	*listarg;
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
	if (!(c.args = list_arg(d, i, word)))
		return (0);
	do_setup(d, &c, word, i);
	c.word = word;
	c.min_line = 0;
	c.num_curr = -1;
	j = complet_arg(&c, tmp);
	if (j == -1)
		return (0);
	insert_word(d, &c, word, i);
	return (j);
}
