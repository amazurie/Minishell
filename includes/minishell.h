/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 16:53:03 by amazurie          #+#    #+#             */
/*   Updated: 2017/06/27 10:40:09 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <termios.h>
# include <stdio.h>
# include <signal.h>
# include <curses.h>
# include <term.h>
# include <dirent.h>

# define ERR_COL		"\e[31m"
# define LIGHTRED_COL	"\e[1;31m"
# define DEFAULT_COL	"\e[0m"
# define PROMPT_COL		"\e[1;36m"
# define PROMPTGIT_COL	"\e[0;94m"
# define MAX_HISTORY	5000
# define LIMIT_LINE		16384

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
	int				*i;
	int				is_term;
}					t_data;

char				*get_elem(t_env *env, char *elem);
int					exec(t_env **env, char *line, t_hist *hist);
int					built_in(t_env **env, char **lstav, t_hist *hist);
t_env				*char_to_lst(char **env);
t_env				*default_env(void);
void				display_env(t_env *env, int color);
void				set_env(t_env **env, char *av);
int					in(t_data **d, char *tmp);
void				unset_env(t_env **env, char **lstav);
void				del_elem(t_env **env, char *elem);
int					cd(char **path, t_env *env);
void				add_hist(t_hist **lst, char *hist);
void				display_hist(t_hist *hist, char *content);
int					disp_hist_next(t_data **d, int **i);
int					disp_hist_prec(t_data **d, int **i);
void				ssupprchr(char **s, int pos);
void				saddchr(char **s, char c, int pos);
char				**splitsemicolon(char *s);
void				get_ch(char **tmp);
int					gest_spekey(char *tmp, t_data **d, int **i);
void				display_prompt(void);
int					del_line(char **line, char *tmp, int **i);
void				del_hist(t_hist *hist);
void				del_env(t_env **e);
void				free_tab(char **tabl);
int					test_paths(char **paths);
t_env				*env_cpy(t_env *env);
void				envcom(char **lstav, t_env *env, t_hist *hist);
char				*test_absolute(char *command);
char				*get_prompt(void);
void				maxline(t_data **d, char *tmp, int **i);
void				del_in(t_data **d, int **i);
int					del_key(char *tmp, int **i, t_data **d);
void				erase_printline(t_data **d, int **i);
int					is_onlytab(char *s);
void				check_dotdot(char **tmp, char **path);
void				builtu_env(char **lstav, t_env **envcpy, size_t *i);
void				echo_doing(char **lstav, t_env **env);
int					is_siginted(int sig);
char				**lst_to_char(t_env *env);
char				*check_path(char *path, t_env *env);
t_data				*get_data(t_data *d);
int					leftright_key(t_data **d, char *tmp, int **i);
int					updown_gest(char *tmp, t_data **d, int **i);
void				quote(t_data **d, int **i);
void				curs_right(t_data **d, int **i);
void				curs_left(t_data **d, int **i);
int					change_envpwd(char *tmp, t_env *env);
int					print_error(char *s);
t_data				*data_alloc(char **env);
int					check_openquote(t_data **d);
void				sighandler(int sig);
void				sig_reset(t_data **d, int **i);
void				chr_in(t_data **d, char *tmp, int **i);
int					gest_in(t_data **d, char *tmp, int **i);
void				data_free(t_data**d);

typedef struct		s_arg
{
	int				num;
	char			*elem;
	char			*color;
	struct s_arg	*next;
}					t_arg;

typedef struct		s_compl
{
	char			*line;
	char			*word;
	char			*path_save;
	int				ac;
	int				i4;
	int				min_line;
	int				num_curr;
	int				is_slash;
	int				is_star;
	int				is_dot;
	int				is_term;
	struct s_arg	*args;
}					t_compl;

int					completion(t_data **d, char **tmp, int **i);
t_arg				*list_arg(t_data **d, t_compl *c, char *word, int **i);
char				*recover_wtocompl(t_data **d, int **i);
int					check_command(t_data **d, int **i);
int					complet_arg(t_compl *c, char **tmp);
int					nbrline(t_arg *arg, int w, int *len);
int					nbr_col(t_arg *arg, int *nline);
int					check_winsize(t_compl *c, int *whcl);
void				display_compl(t_compl *c);
int					*get_size(t_compl *c);
int					check_quotecompl(t_data **d, int **i);
char				*recover_wtocompl(t_data **d, int **i);
void				free_complargs(t_arg *arg);
void				compl_addcolor(t_arg **tmplist, char *path, char *arg);
int					compl_star(t_data **d, t_compl *c, int **i);
int					get_sline(t_compl *c, int col);
int					*get_size(t_compl *c);
t_arg				*list_content(t_compl *c, char *path, char *word);
void				prep_compldisplay(t_compl *c, int *whcl);
void				compl_curspos(t_compl *c, char *word);

#endif
