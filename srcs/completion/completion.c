#include "minishell.h"

int		check_quotecompl(t_data **d, int **i)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while ((*d)->line[k] && k <= (*i)[4])
	{
		if ((*d)->line[k] == 34 && j != 2)
		{
			if (j == 0)
				j = 1;
			else
				j = 0;
		}
		else if ((*d)->line[k] == 39 && j != 1)
		{
			if (j == 0)
				j = 2;
			else
				j = 0;
		}
		k++;
	}
	return (j);
}

char	*recover_wtocompl(t_data **d, int **i)
{
	char	*word;
	int		j;
	int		k;

	k = 0;
	if (check_quotecompl(d, i))
		k = 1;
	if (!(word = (char *)ft_memalloc(301)))
		return (NULL);
	j = (*i)[4] - 1;
	while (j > (*i)[6] && ((k == 1 && ((*d)->line[j] != '"'
						|| (*d)->line[j] != '\'')) || (k == 0 && (*d)->line[j] != ' ')))
		j--;
	while ((*d)->line[j] == ' ')
		j++;
	if (j > (*i)[4] || (*i)[4] - j > 300)
		return (NULL);
	ft_strncat(word, ((*d)->line + j), (*i)[4] - j);
	return (word);
}

int		check_command(t_data **d, int **i)
{
	int		j;

	if ((*i)[4] == 0)
		return (0);
	j = (*i)[4] - 1;
	while (j > (*i)[6] && (*d)->line[j] != 32 && (*d)->line[j] != 34
			&& (*d)->line[j] != 96)
		j--;
	if (j == (*i)[6])
		return (0);
	while (j > (*i)[6] && ((*d)->line[j] == 32 || (*d)->line[j] == 34
				|| (*d)->line[j] == 96))
		j--;
	if ((*d)->line[j] == 32)
		return (0);
	return (1);
}

int		completion(t_data **d, char **tmp, int **i)
{
	t_compl	c;
	t_arg	*listarg;
	t_arg	*args;
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
	if (!(listarg = list_arg(d, i, word)))
		return (0);
	c.line = ft_strdup((*d)->line);
	j = 0;
	if (word)
		j = ft_strlen(word);
	c.i4 = (*i)[4] - j;
	while (j-- > 0)
	{
		ssupprchr(&(c.line), c.i4);
		curs_left(d, i);
	}
	args = listarg;
	j = 0;
	while (args)
	{
		args->num = j;
		args = args->next;
		j++;
	}
	c.word = word;
	c.ac = j - 1;
	c.min_line = 0;
	c.args = listarg;
	c.num_curr = -1;
	c.nbr_line = 0;
	c.nbr_col = 0;
	j = complet_arg(&c, tmp);
	if (j == -1)
		return (0);
	c.ac = 0;
	if (c.word)
		c.ac = ft_strlen(c.word);
	if (word)
		c.ac -= ft_strlen(word);
	while (c.ac-- > 0)
		curs_left(d, i);
	c.ac = 0;
	if (word)
		c.ac = ft_strlen(word);
	if (c.word)
		chr_in(d, (c.word + c.ac), i);
	return (j);
}
