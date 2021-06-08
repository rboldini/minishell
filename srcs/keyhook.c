#include "../includes/minishell.h"

/*
**	ft_fill_row()
**	just adds the char c to the row that will go to the parser
*/

void	ft_fill_row(t_history *curr, t_shell *minishell, char c)
{
	size_t	len;
	int		i;
	char	*tmp;
	char	temp;

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
	i = curr->index;
	if (!curr->old && minishell->n_up)
	{
		curr->old = ft_strdup(curr->row); //crea un duplicato praticamente
		printf("ho creato un old di curr->row (%s), che é %s\n", curr->row, curr->old);
	}
	if (curr->index < (int)ft_strlen(curr->row))
	{
		temp = curr->row[i];
		curr->row[i] = c;
		write(1, &c, 1);
		while (curr->row[(++i) - 1])
		{
			c = curr->row[i];
			curr->row[i] = temp;
			temp = c;
			write(1, &curr->row[i], 1);
		}
		i = -1;
		while (++i < (int)ft_strlen(curr->row) - curr->index)
			write(1, "\b", 1);
		curr->index++;
	}
	else
		curr->row[curr->index++] = c;
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

int	ft_special_keys(char c, t_shell *minishell)
{
	if (c == 27)
	{
		c = (char)ft_hook_char();
		if (c == 91)
		{
			c = (char)ft_hook_char();
			if (c == 65 || c == 66)
				ft_arrow_ud(c, minishell);
			else if (c == 67 || c == 68)
				ft_arrow_lr(c, minishell->current);
			else if (c == 51)
			{
				c = (char)ft_hook_char();
				if (c == 126)
					ft_process_delete(minishell->current);
			}
			else
				write(1, "\a", 1);
		}
	}
	else if(c == 127)
		ft_process_backspace(minishell->current);
	else if(c == 21) //line clear utility
	{
		int i = 0;
		while(i < (int)ft_strlen(minishell->current->row))
			minishell->current->row[i] = 0;
		write(1, "\r\033[2K", 5);
		write (1, minishell->prompt, ft_strlen(minishell->prompt));
		minishell->current->index = 0;
	}
	else
		return (c);
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

void	ft_new_history(t_history **curr)
{
	t_history *new;

	new = ft_calloc(1, sizeof(t_history));
	ft_memset(new, 0, sizeof(t_history));
	if ((*curr))
		(*curr)->next = new;
	new->next = NULL;
	new->index = 0;
	new->prev = *curr;
	*curr = new;
}

void	hook_line(t_shell *minishell)
{
	char	c;

	c = (char)ft_hook_char();
	minishell->current->row = calloc(1024, sizeof(char));
	while (c != '\n') //fino a che non premo invio
	{
		if (ft_special_keys(c, minishell))
		{
			ft_fill_row(minishell->current, minishell, c);
			write(1, &c, 1);
		}
		c = (char)ft_hook_char();
	}
	if (!minishell->current->old && minishell->n_up)
	{
		minishell->current->old = ft_strdup(minishell->current->row); //crea un duplicato praticamente
		printf("ho creato un old di curr->row (%s), che é %s\n", minishell->current->row, minishell->current->old);
	}
	if (minishell->current->old && minishell->n_up)
	{
		free(minishell->current->row);
		printf("wewew sono entrata\ncurrent row sarebbe %s\n", minishell->current->row);
		free(minishell->tmp->row);
		minishell->tmp->row = ft_strdup(minishell->current->row);
		minishell->tmp->index = (int)ft_strlen(minishell->current->row);
		printf("cursore sta a %i\n", minishell->tmp->index);
		free(minishell->current->row);
		printf("old è %s\n", minishell->current->old);
		minishell->current->row = minishell->current->old;
		minishell->current->old = NULL;
		minishell->current->index = (int)ft_strlen(minishell->current->row);
		minishell->current = minishell->tmp;
		//printf("%s\n", minishell->current->prev->row);
	}
//	while (minishell->current->next->next)
//		minishell->current = minishell->current->next;
	minishell->n_up = 0;
	if (minishell->current->row && ft_strlen(minishell->current->row))
		ft_new_history(&minishell->current);
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
