#include "../includes/minishell.h"

/*
**	ft_fill_row()
**	just adds the char c to the row that will go to the parser
*/

void	ft_fill_row(t_history *curr, char c)
{
	size_t	len;
	char	*tmp;

	len = 0;
	if ((*curr).row)
		len = ft_strlen(curr->row);
	if (!(len % 1023))
	{
		tmp = ft_strdup(curr->row);
		free(curr->row);
		curr->row = ft_calloc(len + 1024, sizeof(char));
		ft_strlcpy(curr->row, tmp, len);
		free(tmp);
	}
	curr->row[len] = c;
	curr->index++;
}

int	ft_hook_char(void)
{
	struct termios	before;
	struct termios	after;
	char			c;
	int				ret;

	tcgetattr (0, &before);
	ft_memcpy(&after, &before, sizeof(struct termios));
	after.c_lflag &= ~(ICANON | ECHO);
	after.c_cc[VMIN] = 1;
	after.c_cc[VTIME] = 0;
	tcsetattr (0, TCSANOW, &after);
	ret = (int)read (0, &c, sizeof(char));
	tcsetattr (0, TCSANOW, &before);
	if (ret == -1)
		exit(1);
	return (c);
}

int	ft_check_special_keys(char c)
{
	int x;

	if (c == 27)
	{
		x = ft_hook_char();
		if (x == 91)
		{
			x = ft_hook_char();
			if (x == 65 || x == 66)
				ft_arrow_ud();
			else if (x == 67 || x == 68)
				ft_arrow_lr();
			else if (x == 51)
			{
				x = ft_hook_char();
				if (x == 126)
			 		ft_process_del();
			}
		}
	}
	else
		return (c);
	write(1, "\a", 1);
	return (0);
}

/*
**TODO:	instead of a single char check for special keys, just take all values
**		and check after ft_fill_row() if the last 1/3/4 char/rs belong to
**		special keys ASCII sequences.
**		In case delete them from row and call the right KEY_FUNCTION().
**		That involve to print the char after ft_fill_row() and
**		ft_check_special_keys() and parse row at every instance of line_hook().
*/

/*
**TODO:	FOR FUN!Reproduce the bell sound when pressing an invalid key like 'ESC'
**		GUESS HOW. (Some hint above/below, search with LOVE).
*/

/*
**TODO:	check	special:
**						backspace = 127
**						delete = 27, 91, 51, 126
**						ctrl + u = 21 (clean line)
**		check	arrows:
**						up = 27, 91, 65
**						down = 27, 91, 66
**						right = 27, 91, 67
**						left = 27, 91, 68
*/

void	hook_line(t_shell *minishell)
{
	char	c;

	c = (char)ft_hook_char();
 	minishell->current = malloc(sizeof(t_history));
 	minishell->current->row = calloc(1024, sizeof(char));
 	while (c != '\n')
 	{
//		printf("%i\n", (int)c);
		ft_fill_row(minishell->current, c);
	 	if (ft_check_special_keys(c))
			write(1, &c, 1);
		c = (char)ft_hook_char();

	}
//	printf("%c", '\a');
//	TODO: create a new instance of t_history HINT: ft_new_history_row();
	printf("\n");
}

/*
**	\0NNN	the character whose ASCII code is NNN (octal)
**	\\		backslash
**	\a		alert
**	\b		backspace
**	\c		produce no further output
**	\f		form feed
**	\n		new line
**	\r		carriage return
**	\t		horizontal tab
**	\v		vertical tab
**
**	Clear line2K mixed to carriage return to clear the line rewriting the PROMPT
**		printf("%c%c[2K", '\r', 27);
**
**	Clear line from cursor posix to the beginning
**		printf("%c[1K", 27);
**
**	Clear line regardless cursor posix
**		printf("%c[2K", 27);
*/
