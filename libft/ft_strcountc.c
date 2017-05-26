#include "libft.h"

int		ft_strcountc(char *s, char c)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (s[++i])
		if (s[i] == c)
			j++;
	return (j);
}
