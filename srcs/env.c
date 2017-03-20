#include "minishell.h"

static void	hand_u(char *uelem, t_env **envcpy)
{
	if (!uelem)
	{
		ft_putstr_fd("env: option requieres an arguments -- u\n", 2);
		ft_putstr_fd("usage [-i] [-u name] [utility [arguments]]\n", 2);
	}
	else if (ft_strchr(uelem, '='))
	{
		ft_putstr_fd("env: unsetenv", 2);
		ft_putstr_fd(uelem, 2);
		ft_putstr_fd(": Invalid argument\n", 2);
	}
	else
		unset_env(envcpy, uelem);
}

static void	envcom2(char **lstav, t_env **envcpy, t_hist *hist)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	k = 1;
	while (lstav[++i])
	{
		j = 0;
		while (lstav[i][++j] && lstav[i][0] == '-')
		{
			if (lstav[i][j] == 'i')
				del_env(envcpy);
			else if (lstav[i][j] == 'u')
			{
				if (lstav[i][j + 1])
				{
					hand_u((lstav[i] + ft_strlen_chr(lstav[i], 'u')),  envcpy);
					j = ft_strlen(lstav[i]);
				}
				else if (lstav[i + 1])
				{
					hand_u(lstav[i + 1], envcpy);
					i ++;
				}
				else
					hand_u(NULL, envcpy);
			}
			else if (lstav[i][j] == 'c')
				k = 2;
			else
			{
				ft_putstr_fd("env: illegal option -- ", 2);
				ft_putchar_fd(lstav[i][j], 2);
				ft_putstr_fd("\nusage [-i] [-u name] [utility [arguments]]\n", 2);
				while (lstav[i])
					i++;
				k = 0;
				i--;
				j = ft_strlen(lstav[i]);
			}
		}
		if (!lstav[i][1] && lstav[i][0] == '-')
			del_env(envcpy);
		if (lstav[i] && lstav[i][0] != '-')
		{
			while (lstav[i])
				exec(envcpy, lstav[i++], hist);
			i--;
		}
	}
	if (k)
		display_env(*envcpy, (k == 2) ? 1 : 0);
}

void		envcom(char **lstav, t_env *env, t_hist *hist)
{
	t_env *envcpy;

	if (!lstav[1])
		display_env(env, 0);
	else
	{
		envcpy = env_cpy(env);
		envcom2(lstav, &envcpy, hist);
		del_env(&envcpy);
	}
}
