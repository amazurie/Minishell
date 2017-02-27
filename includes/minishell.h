#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <sys/wait.h>
# include <termios.h>
# include <stdio.h>

//# define RED			"\e[31m"
# define LIGHT_RED		"\e[1;31m"
//# define GREEN			"\e[32m"
//# define YELLOW			"\e[33m"
//# define BLUE			"\e[34m"
//# define LIGHT_BLU	E	"\e[1;34m"
//# define MAGENTA		"\e[35m"
//# define CYAN			"\e[36m"
# define DEFAULT		"\e[0m"
# define MAX_HISTORY	126

typedef struct	hist_list
{
	int					num;
	char				*hist;
	struct hist_list	*next;
}				h_list;

typedef struct	env_list
{
	char			*elem;
	char			*cont;
	struct env_list	*next;
}				e_list;

char			*get_elem(e_list *env, char *elem);
int				test_paths(char **path);
int				exec(e_list *env, char *line, h_list *hist);
e_list			*char_to_lst(char **env);
void			display_env(e_list *env, char *opt);
void			set_env(e_list **env, char *elem, char *cont);
void			unset_env(e_list **env, char *elem);
void			add_hist(h_list **lst, char *hist);
void			display_hist(h_list *hist);

#endif
