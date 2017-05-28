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
	while (j > (*i)[6] && ((k == 1 && (*d)->line[j] != '"')
				|| (k == 0 && (*d)->line[j] != ' ')))
		j--;
	while ((*d)->line[j] == ' ')
		j++;
	if ((*i)[4] - j > 300)
		return (NULL);
	ft_strncat(word, ((*d)->line + j), (*i)[4] - j);
	return (word);
}

int		check_command(t_data **d, int **i)
{
	int		j;

	j = (*i)[4];
	while (j > (*i)[6] && (*d)->line[j] != 32 && (*d)->line[j] != 34
			&& (*d)->line[j] != 96)
		j--;
	while (j > (*i)[6] && ((*d)->line[j] == 32 || (*d)->line[j] == 34
				|| (*d)->line[j] == 96))
		j--;
	if (((*d)->line[j] == 32) || j == (*i)[6])
		return (0);
	return (1);
}

int		completion(t_data **d, char **tmp, int **i)
{
	t_compl	c;
	t_arg	*listarg;
	t_arg	*args;
	int		j;

	if ((*tmp)[0] != 9 || (*tmp)[1] || (*i)[6] > 0)
		return (0);
	if (!(listarg = list_arg(d, i)))
		return (0);
	args = listarg;
	j = 0;
	while (args)
	{
		args = args->next;
		j++;
	}
	c.ac = j;
	c.min_line = 0;
	c.args = listarg;
	c.num_curr = 0;
	c.nbr_line = 0;
	c.nbr_col = 0;
	c.line = (*d)->line;
	complet_arg(&c, tmp, i);
	return (0);
}
