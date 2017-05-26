#include "libft.h"

int		ft_strisprint(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (ft_isprint(s[i]) == 0)
			return (0);
	return (1);
}
