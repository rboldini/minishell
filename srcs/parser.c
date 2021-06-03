/*
**	The Parser is the software component that reads the command line such as
**	“ls -al” and puts it into a data structure called Command Table that will
**	store the commands that will be executed.
*/

#include "../includes/parser.h"
#include "../includes/minishell.h"

#include <stdio.h>

typedef struct	s_cmd
{
	char			**arr;
	int				len;
	struct s_cmd	*next;
	int				next_type;
	FILE			*file_in;
}				t_cmd;

void	start_parsing(char *cmd)
{
	t_cmd	*cmd_table;
	char	**tmp;

	
}

int	main(int argv, char **argc)
{
	start_parsing(argc[1]);
	return (0);
}


/*

cmd > file1 > file2 > file3
cmd1 | cmd2 < file_in
cmd > file_out
cmd >> file_app
cmd < file_in
cmd1 ; cmd2

*/