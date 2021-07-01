#ifndef MINISHELL_MINISHELL_H
#define MINISHELL_MINISHELL_H

/*
 *	; should separate commands like bash
 *	< infile
 *	> outfile
 *	| redirect output
 */

#include <stdlib.h>
#include "../libft/libft.h"
#include "../ft_printf_fd/ft_printf.h"
#include "color.h"
# include <curses.h>
# include <ncurses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <string.h>
# include <term.h>
# include <unistd.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

enum e_cmd
{
	CMD_PWD,
	CMD_CD,
	CMD_ENV,
	CMD_EXP,
	CMD_UNSET,
	CMD_ECHO,
	CMD_EXIT,
	CMD_RUN,
	ENV_DECLA,
};

typedef struct s_history
{
	char	*row;
	char	*old;
	int		index;
	struct	s_history *prev;
	struct	s_history *next;
}				t_history;

typedef struct s_env
{
	char	*env_name;
	char	*env_value;
	int		exp; // 0 = not_exported 	1 = exported	2 = semi-exported
	struct	s_env *next_env;
}				t_env;

typedef struct	s_shell
{
	char		*prompt;
	t_history	*current;
	t_history	*tmp;
	int			in_dred;
	int			n_up;
	int			abort;
	int			abort_dred;
	int 		pid;
	t_env		*env;
}				t_shell;

t_shell *minishell;

typedef struct	s_cmd
{
	char			**arr;
	char			*eof;
	int				has_dred;
	int				len;
	struct s_cmd	*next;
	int				has_previous;
	//int				out_append;
	int				file_in;	//0
	int				file_out;	//1
	int				err_out;	//2
	int				is_append;
}				t_cmd;

typedef struct s_cv
{
	t_cmd	**cmd_arr;
	t_cmd	*comm;
	t_cmd	*tmp_comm;
	char	**arr;
	char	*buff;
	int		stage;
	int		isb;
}				t_cv;

/*
** Parser
*/

void	hook_line(t_shell *minishell);
t_cmd	**start_parsing(const char *cmd);
t_env	*init_env(char **env);
void	ft_free_matrix(char **matrix);
void	run_command(int code, t_cmd *cmd, t_env *env);
void	ctrl_c(void);
char	*app_char(const char *cmd, int *i, char *buff);
char	*elab_dollar(const char *src, int *i, char *dst);
char	*escape_slash(const char *src, int *i, char *dst);
char	**append_to_arr(const char *str, int *len, char **arr);
char	*elab_quote(const char *src, int *i, char *dst);
char	*elab_dquote(const char *src, int *i, char *dst);
int		next_char(char *str, char c, int start);
int		is_break(const char *cmd, int i);
char	*next_token(const char *cmd, int *i, int *isb);
void	init_cmd(t_cmd *comm);
t_cmd	**add_tcmd(t_cmd **cmd_arr, t_cmd *comm, t_cv *cv);

void	finalize_history(void);
void	ft_arrow_down(void);
void	ft_process_delete(t_history *curr);

/*
** ENV - EXPORT
*/

void	ft_free_env(t_env *env);
void	ft_addback_env(t_env **env, t_env *new_env);
void	create_new_env(t_env **env, char *raw_env, int export);
void	ft_env(t_env *env, int ac, char **av);
void	ft_export_env(t_env *env, char *str);
void	ft_export(t_env *env, int ac, char **av);
void	unset_env(t_env **env, char* name);
void	set_env(t_env **env, char* name);
char	*ft_getenv(t_env *env, char *name);
void	ft_unset(t_env **env, int ac, char **av);
void	edit_env(t_env **env,char *name, char *new_value);
t_env	*check_existing_env(t_env *env, char *name);
void	ft_home_end(int c, t_shell *minishell);
void	ft_move_word(int c, t_history *curr);
int		ft_check_ctrl(int *c);
char	**exported_env_matrix(t_env *env);
void	ft_runner(t_env *env, char **av, char *path);
void 	forker(t_cmd *cmd, t_env *env, int cmd_code);
void	ft_hook_signal(void);
void	free_history(t_history *curr);
char	*d_redirect(char *eof);

/*
** CD
*/

void	ft_cd(int ac, char **av, t_env **env);

/*
** PDW
*/

void	ft_pwd();

/*
** PROMPT
*/

void set_prompt(char *str);
void get_prompt();

/*
** CMD
*/

void	ft_echo(int ac, char **av);
int		ft_hook_char(void);
void	ft_arrow_ud(int x, t_shell *minishell);
void	ft_arrow_lr(int x, t_history *curr);
int 	ft_process_backspace(t_history *curr);
void	ft_process_delete(t_history *curr);
void	ft_new_history(t_history **curr);
void	free_old(t_history *curr);
void	ft_fill_row(t_history *curr, char c);
void	ft_exit(t_shell *minishell);

/*
** EXECUTOR
*/

void	ft_executor(t_cmd *cmd, t_env *env);
void	ft_error(int errnum, char *str, int cmd_flag);
int		ft_isdir(char *path);
int		ft_isfile(char *path);

/*
** DEBUG
*/

void	ft_print_env(t_env *env);

#endif //MINISHELL_MINISHELL_H