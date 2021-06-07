#ifndef MINISHELL_MINISHELL_H
#define MINISHELL_MINISHELL_H

/*
 *	; should separate commands like bash
 *	< infile
 *	> outfile
 *	| redirect output
 *
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

typedef struct s_history
{
	char	*row;
	int		index;
	struct	s_history *prev;
	struct	s_history *next;
}				t_history;

typedef struct	s_shell
{
	char		*prompt;
	t_history	*current;
	t_history	*tmp;
	int			n_up;
	int			n_down;
}				t_shell;

typedef struct s_env
{
	char	*env_name;
	char	*env_value;
	int		exp; // 0 = not_exported 	1 = exported
	struct	s_env *next_env;
}				t_env;

typedef struct	s_cmd
{
	char			**arr;
	int				len;
	struct s_cmd	*next;
	//int				out_append;
	int				file_in;	//0
	int				file_out;	//1
	int				file_out_app;	//1
	int				err_out;	//2
	char			*filename_in;
	char			*filename_out;
	char			*filename_out_app;
}				t_cmd;

/*
 *
 */

/*
** Parser
*/

void	hook_line(t_shell *minishell);
t_cmd	*start_parsing(const char *cmd);
t_env	*init_env(char **env);
void	ft_free_matrix(char **matrix);

/*
** ENV - EXPORT
*/

void	ft_free_env(t_env *env);
void	ft_addback_env(t_env **env, t_env *new_env);
void	create_new_env(t_env **env, char *raw_env, int export);
void	ft_env(t_env *env);
void	ft_export_env(t_env *env, char *str);
void	unset_env(t_env **env, char* name);
void	set_env(t_env **env, char* name);
char	*ft_getenv(t_env *env, char *name);

/*
** CD
*/

void	ft_cd(int ac, char **av, t_env *env);


/*
** PROMPT
*/

void set_prompt(t_shell *minishell, char *str);
char* getprompt(t_shell *minishell);

/*
** CMD
*/

void	command_handle(char *command, t_shell *minishell);
void	ft_echo(int ac, char **av);

int	ft_hook_char(void);
void	ft_arrow_ud(/*int x, t_history *curr*/);
void	ft_arrow_lr(int x, t_history *curr);
int 	ft_process_backspace(t_history *curr);
void	ft_process_delete(t_history *curr);
void	ft_new_history(t_history **curr);
#endif //MINISHELL_MINISHELL_H