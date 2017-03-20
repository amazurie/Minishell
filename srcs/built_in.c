#include "minishell.h"

static int	built_in2(t_env **env, char **lstav, t_hist *hist)
{
	if (ft_strcmp(lstav[0], "history") == 0 && !lstav[1])
		display_hist(hist);
	else if (ft_strcmp(lstav[0], "cd") == 0)
		cd(lstav, *env);
	else if (ft_strcmp(lstav[0], "exit") == 0 && !lstav[1])
		return (-1);
	else if (ft_strcmp(lstav[0], "clear") == 0 && !lstav[1])
		ft_putstr("\033c");
	else
		return (0);
	return (1);
}

int		built_in(t_env **env, char **lstav, t_hist *hist)
{
	size_t	len;

	if (!lstav[0])
		return (0);
	else if (ft_strcmp(lstav[0], "env") == 0)
		envcom(lstav, *env, hist);
	else if (ft_strcmp(lstav[0], "setenv") == 0 && lstav[1])
		set_env(env, lstav[1], lstav[2]);
	else if (ft_strcmp(lstav[0], "unsetenv") == 0 && lstav[1])
		unset_env(env, lstav[1]);
	else if (ft_strcmp(lstav[0], "pwd") == 0)
	{
		if (lstav[1])
			ft_putstr_fd("pwd: too many arguments", 2);
		else
			ft_putstr(get_elem(*env, "PWD"));
		ft_putstr("\n");
	}
	else
		return (built_in2(env, lstav, hist));
	return (1);
}
