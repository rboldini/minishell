#include "../includes/minishell.h"

void	ft_arrow_ud(int x, t_shell *minishell)
{
	if (x == 65)
	{
		if(minishell->current->prev)
		{
			if (minishell->n_up == 0)
				minishell->tmp = minishell->current;
			printf("\ntmp row é %s\n", minishell->tmp->row);
			minishell->current = minishell->current->prev;
			write(1, "\r\033[2K", 5);
			write(1, minishell->prompt, ft_strlen(minishell->prompt));
			minishell->current->old = ft_strdup(minishell->current->row);
			write(1, minishell->current->row, ft_strlen(minishell->current->row));
			minishell->n_up++;
		}
	}
	else
	{
		if (minishell->current->next)
		{
			minishell->n_up--;
			if (ft_strlen(minishell->current->row) && minishell->n_up == 0)
				minishell->tmp = minishell->current;
			write(1, "\r\033[2K", 5);
			write(1, minishell->prompt, ft_strlen(minishell->prompt));
			//while (minishell->current->prev && i++ < minishell->n_up)
			minishell->current = minishell->current->next;
			//	printf("%s\n", minishell->current->row);
			write(1, minishell->current->row,
				  ft_strlen(minishell->current->row));
		}
	}
}

void	ft_arrow_lr(int x, t_history *curr)
{
	if (x == 68 && curr->index > 0)//sinistra
	{
		write(1, "\b", 1);
		curr->index--;
	}
	else if(x == 67 && curr->index != (int)ft_strlen(curr->row))
	{
		write(1, "\033[C", 3);
		curr->index++;
	}
	else
		write(1, "\a", 1);
}

int 	ft_process_backspace(t_history *curr)
{
	int	i;

	i = curr->index;
	if (i > 0 && i < (int)ft_strlen(curr->row))
	{
		write(1, "\b", 1);
		while (i < (int)ft_strlen(curr->row))
		{
			curr->row[i - 1] = curr->row[i];
			write(1, &curr->row[i - 1], 1);
			i++;
		}
		curr->row[ft_strlen(curr->row) - 1] = 0;
		write(1, " \b", 2);
		i = -1;
		while (++i <= (int)ft_strlen(curr->row) - curr->index)
			write(1, "\b", 1);
		curr->index--;
	}
	else if (i == (int)ft_strlen(curr->row) && i > 0)
	{
		curr->row[i - 1] = 0;
		write(1, "\b \b", 3);
		curr->index--;
	}
	else
		write(1, "\a", 1);
	return (1);
}

void	ft_process_delete(t_history *curr)
{
	int	i;
	int	len;

	i = curr->index;
	len = (int)ft_strlen(curr->row);
	if (curr->index != len)
	{
		while (i < (int)ft_strlen(curr->row))
		{
			curr->row[i] = curr->row[i + 1];
			write(1, &curr->row[i], 1);
			i++;
		}
		curr->row[i] = 0;
		write(1, " ", 1);
		i = 0;
		while (i < len - curr->index)
		{
			write(1, "\b", 1);
			i++;
		}
	}
	else
		write(1, "\a", 1);
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
	minishell->current->row = ft_calloc(1024, sizeof(char));
	while (c != '\n') //fino a che non premo invio
	{
		if (ft_special_keys(c, minishell))
		{
			ft_fill_row(minishell->current, c);
			write(1, &c, 1);
		}
		c = (char)ft_hook_char();
	}
	if (minishell->n_up)
	{
		minishell->current->prev = minishell->current->prev;
		minishell->tmp->row = minishell->current->row;
		minishell->current->row = minishell->current->old;
		minishell->tmp->index = minishell->current->index;
		minishell->current = minishell->tmp;
		//strcmp()
		printf("\ncurrent row %s tmp row %s\n", minishell->current->row, minishell->tmp->row);
		//minishell->tmp = minishell->current;
		// if (strcmp(minishell->current->old, minishell->current->row))
		// {
		// 	minishell->tmp->row = minishell->current->row;
		// 	minishell->tmp->index = minishell->current.
		// 	minishell->current = minishell->tmp;
		// 	//free(minishell->tmp);
		// 	//int i = minishell->n_up;
		// 	//while ()
			printf("siamo saliti %i volte\n", minishell->n_up);
			//printf("wewe siamo diversi!!! ritorna: %i\n", strcmp(minishell->current->old, minishell->current->row));
	//	}
	}
	minishell->n_up = 0;
	ft_new_history(&minishell->current);
	//printf("\n%p <- prev prev\n%p <- prev\n%p <- prev next\n%p <- current\n%p <- next\n", minishell->current->prev->prev, minishell->current->prev, minishell->current->prev->next, minishell->current, minishell->current->next);
	write(1, "\n", 1);
}