/*
**	The Parser is the software component that reads the command line such as
**	“ls -al” and puts it into a data structure called Command Table that will
**	store the commands that will be executed.
*/

// #include "../includes/parser.h"
#include "../includes/minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IN_QUOTE 1
#define IN_DQUOTE 2

typedef struct	s_comm
{
	char			**arr;
	int				len;
	struct s_cmd	*next;
	int				next_type;
	FILE			*file_in;
}				t_comm;

char	**append_to_arr(const char *str, int *len, char **arr)
{
	char	**tmp;
	int		i;
	int		n;

	n = *len;
	tmp = malloc(sizeof(char *) * (n + 1));
	i = 0;
	while (i < n)
	{
		tmp[i] = arr[i];
		i++;
	}
	// remove system strdup
	tmp[i] = strdup(str);
	free(arr);
	(*len)++;
	return (tmp);
}

typedef struct s_flags
{
	int		in_dquote;
	int		in_quote;
	int		is_var;
}				t_flags;

void	expand_env(char *str)
{
	int	is_quote;
	int	is_dquote;

	is_dquote = 0;
	is_quote = 0;
}

void	start_parsing(const char *cmd)
{
	t_comm	*cmd_table;
	char	**arr;
	int		*to_expand;
	int		len;
	char	**spc_spl;

	arr = malloc(0);
	len = 0;
	spc_spl = ft_split(cmd, ' ');

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

bash-3.2$ echo "$TERM"
xterm-256color

bash-3.2$ echo '$TERM'
$TERM

bash-3.2$ echo "\'"
\'

bash-3.2$ echo '\"'
\"
*/