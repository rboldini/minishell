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

typedef struct	s_cmd
{
	char		**cmd_table;
}				t_cmd;


#define CMD_ECHO "echo"
#define CD "cd"
#define PWD "pwd"
#define EXPORT "export"
#define UNSET "unset"
#define ENV "env"
#define EXIT "exit"

enum e_token
{
	CHAR_GENERAL=	-1,
	CMD			=	0,
	INFILE		=	'<',
	OUTFILE		=	'>',
	PIPE		=	'|',

};

typedef struct	s_scmd
{
	int cmd;
	char **arg;
}				t_scmd;

typedef struct s_cmdt
{
	t_scmd	*table;
	int		n_sep;
}				t_cmdt;

typedef struct s_history
{
	char	*row;
	int		index;
	struct	s_history *prev;
	struct	s_history *next;
}				t_history;

typedef struct	s_shell
{
	char *prompt;
	t_history *current;
}				t_shell;

/*
 *
 */

/*
** LEXAR
*/

void	hook_line(t_shell *minishell);

/*
** PROMPT
*/

void set_prompt(t_shell *minishell, char *str);
char* getprompt(t_shell *minishell);

/*
** CMD
*/

void	command_handle(char *command, t_shell *minishell);
void	ft_echo(t_shell *minishell);
int 	ft_pwd(void);
void	ft_cd(t_shell *minishell);

int	ft_hook_char(void);
int ft_process_del(char c, t_shell *minishell);
#endif //MINISHELL_MINISHELL_H
