#ifndef MINISHELL_MINISHELL_H
#define MINISHELL_MINISHELL_H

#include <signal.h>

typedef struct s_cmd
{
	char		**cmd_table;
}				t_cmd;

typedef struct SimpleCommand
{
	int		numberOfAvailableArguments;		// Available space for arguments currently preallocated int _numberOfAvailableArguments;
	int		numberOfArguments;				// Number of arguments int _numberOfArguments;
	char	**arguments;					// Array of arguments char ** _arguments;
	void 	&(f)ft_SimpleCommand():
}			SimpleCommand;

#endif //MINISHELL_MINISHELL_H