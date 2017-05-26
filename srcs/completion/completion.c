#include "minishell.h"

char	*recover_wtocompl(t_data **d, int **i)
{
	char	*word;
	int		j;
	int		k;

	k = 0;
	if (check_openquote(d))
		k = 1;
	if (!(word = (char *)ft_memalloc(301)))
		return (NULL);
	j = (*i)[4];
	while (j > (*i)[6] && ((k == 1 && (*d)->line[j] != '"')
					|| (k == 0 && (*d)->line[j] != ' ')))
			j--;
	k += ((*d)->line[j] == ' ') ? 1 : 0;
	ft_strncat(word, ((*d)->line + j + k), (*i)[4] - (j + k));
	return (word);
}

t_list	list_arg(t_data **d, int **i)
{
	t_list	list;
	char	*word;

	word = recover_wtocompl(d, i);
	return (list);
}

int		completion(t_data **d, char *tmp, int **i)
{
	t_list	listarg;

	if (tmp[0] != 9 || tmp[1])
		return (0);
	list_arg(d, i);
	return (0);
}
