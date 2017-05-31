#include "minishell.h"

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
