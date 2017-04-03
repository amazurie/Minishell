/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 16:53:03 by amazurie          #+#    #+#             */
/*   Updated: 2017/04/03 16:56:38 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <sys/wait.h>
# include <termios.h>
# include <stdio.h>
# include <signal.h>
# include <sys/stat.h>

# define ERR_COL	"\e[31m"
# define LIGHTRED_COL	"\e[1;31m"
# define DEFAULT_COL	"\e[0m"
# define PROMPT_COL		"\e[1;36m"
# define MAX_HISTORY	256

typedef struct		s_hist
{
	int				num;
	char			*hist;
	struct s_hist	*next;
}					t_hist;

typedef struct		s_env
{
	char			*elem;
	char			*cont;
	struct s_env	*next;
}					t_env;

typedef struct		s_data
{
	struct s_hist	*hist;
	struct s_env	*env;
	char			*line;
	char			*buffline;
	char			*prompt;
}					t_data;

char				*get_elem(t_env *env, char *elem);
int					exec(t_env **env, char *line, t_hist *hist);
int					built_in(t_env **env, char **lstav, t_hist *hist);
t_env				*char_to_lst(char **env);
void				display_env(t_env *env, int color);
void				set_env(t_env **env, char *elem, char *cont);
int					gest_in(t_data **d, char *tmp, int **i);
void				unset_env(t_env **env, char *elem);
int					cd(char **path, t_env *env);
void				add_hist(t_hist **lst, char *hist);
void				display_hist(t_hist *hist);
int					disp_hist_next(t_hist *lst, int **i, char **line);
int					disp_hist_prec(t_hist *lst, int **i, char **line);
void				ssupprchr(char **s, int pos);
void				saddchr(char **s, char c, int pos);
char				**splitsemicolon(char *s);
void				handbackslash(char **s);
void				get_ch(char **tmp);
int					gest_spekey(char *tmp, t_data **d, int **i);
void				display_prompt(void);
int					del_line(char **line, char *tmp, int **i);
void				del_hist(t_hist *hist);
void				del_env(t_env **e);
void				free_tab(char **tab);
int					test_paths(char **paths);
t_env				*env_cpy(t_env *env);
void				envcom(char **lstav, t_env *env, t_hist *hist);
char				*test_absolute(char *command);
char				*get_prompt(void);
void				maxline(char **line, int **i);
void				del_in(t_data **d, int **i);
int					del_key(char *tmp, int **i, t_data **d);
void				erase_printline(t_data **d, int **i);
int					is_onlytab(char *s);
void				check_dotdot(char **tmp, char **path);

#endif
