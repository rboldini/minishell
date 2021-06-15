#include "../../includes/minishell.h"

int ft_special_keys(int c, t_shell *minishell)
{
	if (c == 27)
	{
		c = ft_hook_char();
		if (c == 91)
		{
			c = ft_hook_char();
			if (c == 65 || c == 66)
				ft_arrow_ud(c, minishell);
			else if (c == 67 || c == 68)
				ft_arrow_lr(c, minishell->current);
			else if (c == 51)
			{
				c = ft_hook_char();
				if (c == 126)
					ft_process_delete(minishell->current);
			}
			else if (c == 72 || c == 70)
				ft_home_end(c, minishell);
			else if (c == 49)
			{
				if (ft_check_ctrl(&c))
					ft_move_word(c, minishell->current);
			}
			else
				write(1, "\a", 1);
		}
	}
	else if(c == 127 || c == 8)
		ft_process_backspace(minishell->current);
	else if (c == 9)
		write(1, "\a", 1);
	else if(c == 21)
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

void	ft_fill_row(t_history *curr, char c)
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
	if (curr->index < (int)ft_strlen(curr->row))
	{
		temp = curr->row[i];
		curr->row[i] = c;
		write(1, &c, 1);
		while (curr->row[i])
		{
			c = curr->row[i + 1];
			curr->row[i + 1] = temp;
			temp = c;
			write(1, &curr->row[i + 1], 1);
			i++;
		}
		i = -1;
		while (++i < (int)ft_strlen(curr->row) - curr->index)
			write(1, "\b", 1);
		curr->index++;
	}
	else
		{
			i = curr->index;
			curr->row[i] = c;
			curr->index++;
	 	}
}

void	ft_new_history(t_history **curr)
{
	t_history *new;

	new = ft_calloc(1, sizeof(t_history));
	ft_memset(new, 0, sizeof(t_history));
	if ((*curr))
		(*curr)->next = new;
	new->row = malloc(0);
	new->next = NULL;
	new->index = 0;
	new->prev = *curr;
	*curr = new;
}

void	hook_line(t_shell *minishell)
{
	char	c;

	c = (char)ft_hook_char();
	free (minishell->current->row);
	minishell->current->row = ft_calloc(1024, sizeof(char));
	while (c != '\n')
	{
		if (ft_special_keys(c, minishell) && ft_isprint(c))
		{
			ft_fill_row(minishell->current, c);
			write(1, &c, 1);
		}
		c = (char)ft_hook_char();
	}
	if (minishell->n_up)
	{
		ft_bzero(minishell->tmp->row, ft_strlen(minishell->tmp->row));
		ft_strlcpy(minishell->tmp->row, minishell->current->row, ft_strlen(minishell->current->row) + 1);
		ft_bzero(minishell->current->row, ft_strlen(minishell->current->row));
		ft_strlcpy(minishell->current->row, minishell->current->old, ft_strlen(minishell->current->old) + 1 );
		free (minishell->current->old);
		minishell->current->old = NULL;
		minishell->tmp->index = (int)ft_strlen(minishell->tmp->row);
		minishell->current = minishell->tmp;
		free_old(minishell->current);
	}
	minishell->current->index = (int)ft_strlen(minishell->current->row);
	minishell->n_up = 0;
	write(1, "\n", 1);
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
