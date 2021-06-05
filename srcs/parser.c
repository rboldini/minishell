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

typedef struct	s_comm
{
	char			**arr;
	int				len;
	//struct s_cmd	*next;
	int				next_type;
	FILE			*file_in;	//0
	FILE			*file_out;	//1
	FILE			*err_out;	//2
}				t_comm;

char	**append_to_arr(const char *str, int *len, char **arr)
{
	char	**tmp;
	int		i;

	tmp = malloc(sizeof(char *) * (*len + 1));
	i = 0;
	while (i < *len)
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

char	*app_char(const char *cmd, int *i, char *buff)
{
	char	*cc;
	char	*tmp;

	cc = malloc(sizeof(char) * 2);
	cc[0] = *(cmd + *i);
	cc[1] = 0;
	tmp = ft_strjoin(buff, cc);
	free(cc);
	free(buff);
	(*i)++;
	return (tmp);
}

char	*elab_dollar(const char *src, int *i, char *dst)
{
	char	c;
	char	*var_name;
	char	*var_value;
	char	*tmp;

	var_name = malloc(sizeof(char));
	var_name[0] = 0;
	c = *(src + *i + 1);
	/*
	if (c == '?')
	{
		(*i)++;
		var_value = getenv("?");
		if (var_value)
		{
			tmp = ft_strjoin(dst, var_value);
			free(dst);
			dst = tmp;
		}
		free(var_name);
		(*i)++;
		return (dst);
	}
	*/
	if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_'))
	{
		dst = app_char(src, i, dst);
	}
	else
	{
		(*i)++;
		c = *(src + *i);
		while ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_')
		{
			var_name = app_char(src, i, var_name);
			c = *(src + *i);
		}
		var_value = getenv(var_name);
		if (var_value)
		{
			tmp = ft_strjoin(dst, var_value);
			free(dst);
			dst = tmp;
		}
	}
	free(var_name);
	return (dst);
}

char	*elab_quote(const char *src, int *i, char *dst)
{
	int		valid;

	valid = 0;
	(*i)++;
	while (*(src + *i))
	{
		if (*(src + *i) == '\'')
		{
			(*i)++;
			valid = 1;
			break ;
		}
		dst = app_char(src, i, dst);
	}
	return (dst);
}

char	*elab_dquote(const char *src, int *i, char *dst)
{
	int		valid;

	valid = 0;
	(*i)++;
	while (*(src + *i))
	{
		if (*(src + *i) == '"')
		{
			(*i)++;
			valid = 1;
			break ;
		}
		else if (*(src + *i) == '$')
			dst = elab_dollar(src, i, dst);
		else
			dst = app_char(src, i, dst);
	}
	return (dst);
}

int		next_char(char *str, char c, int start)
{
	while (*(str + start))
	{
		if (*(str + start) == c)
			return (start);
		start++;
	}
	return (-1);
}

int		is_break(char c)
{
	if (c == ' ' || c == 0 || c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

void	start_parsing(const char *cmd)
{
	t_comm	*comm;
	char	**arr;
	int		len;
	int		i;
	char	*buff;

	comm = malloc(sizeof(t_comm));
	arr = malloc(0);
	len = 0;
	i = 0;
	while (*(cmd + i))
	{
		buff = malloc(sizeof(char));
		buff[0] = 0;
		while (!is_break(*(cmd + i)))
		{
			if (*(cmd + i) == '\'')
				buff = elab_quote(cmd, &i, buff);
			else if (*(cmd + i) == '"')
				buff = elab_dquote(cmd, &i, buff);
			else if (*(cmd + i) == '$')
				buff = elab_dollar(cmd, &i, buff);
			else
				buff = app_char(cmd, &i, buff);
		}
		if (*(cmd + i) == '|')
		{
			buff = app_char(cmd, &i, buff);
			break ;
		}
		if (ft_strlen(buff))
			arr = append_to_arr(buff, &len, arr);
		if (*(cmd + i) != 0)
			i++;
	}
	for (int k = 0; k < len; k++)
	{
		printf("%s\n", arr[k]);
	}
}

int	main(int argv, char **argc)
{
	/*for (int i = 1; i < argv; i++)
		start_parsing(argc[i]);*/
	char *str = "qui|quo|stocazzo $? ciao";
	printf("input: %s\n", str);
	start_parsing(str);
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

bash-3.2$ echo "ciao   test"
ciao   test

bash-3.2$ echo ciao   test
ciao test

bash-3.2$ echo 'ciao   test'
ciao   test

bash-3.2$ ARG="ciao   test"
bash-3.2$ echo $ARG
ciao test
*/