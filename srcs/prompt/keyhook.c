#include "../../includes/minishell.h"

void	special_keys2(int c)
{
	c = ft_hook_char();
	if (c == 65 || c == 66)
		ft_arrow_ud(c, g_shell);
	else if (c == 67 || c == 68)
		ft_arrow_lr(c, g_shell->current);
	else if (c == 51)
	{
		c = ft_hook_char();
		if (c == 126)
			ft_process_delete(g_shell->current);
	}
	else if (c == 72 || c == 70)
		ft_home_end(c, g_shell);
	else if (c == 49)
	{
		if (ft_check_ctrl(&c))
			ft_move_word(c, g_shell->current);
	}
	else
		write(1, "\a", 1);
}

int	ft_special_keys(int c, t_shell *g_shell)
{
	if (c == 27)
	{
		c = ft_hook_char();
		if (c == 91)
			special_keys2(c);
	}
	else if (c == 4)
	{
		if (!g_shell->current->row[0])
			ft_exit(g_shell);
	}
	else if (c == 127 || c == 8)
		ft_process_backspace(g_shell->current);
	else if (c == 9)
		write(1, "\a", 1);
	else if (c == 21)
	{
		ft_bzero(g_shell->current->row, ft_strlen(g_shell->current->row));
		write(1, "\r\033[2K", 5);
		write (1, g_shell->prompt, ft_strlen(g_shell->prompt));
		g_shell->current->index = 0;
	}
	else
		return (c);
	return (0);
}

void	fill_row2(char c, int i)
{
	char	temp;

	temp = g_shell->current->row[i];
	g_shell->current->row[i] = c;
	write(1, &c, 1);
	while (g_shell->current->row[i])
	{
		c = g_shell->current->row[i + 1];
		g_shell->current->row[i + 1] = temp;
		temp = c;
		write(1, &g_shell->current->row[i + 1], 1);
		i++;
	}
	i = -1;
	while (++i < (int)ft_strlen(g_shell->current->row)
		- g_shell->current->index)
		write(1, "\b", 1);
	g_shell->current->index++;
}

void	ft_fill_row(t_history *curr, char c)
{
	size_t	len;
	int		i;
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
	i = curr->index;
	if (curr->index < (int)ft_strlen(curr->row))
		fill_row2(c, i);
	else
	{
		i = curr->index;
		curr->row[i] = c;
		curr->index++;
	}
}

void	hook_line(t_shell *g_shell)
{
	char	c;

	free (g_shell->current->row);
	g_shell->current->row = ft_calloc(1024, sizeof(char));
	while (1)
	{
		c = (char)ft_hook_char();
		if (c == '\n')
			break ;
		if (ft_special_keys(c, g_shell) && ft_isprint(c))
		{
			ft_fill_row(g_shell->current, c);
			write(1, &c, 1);
		}
	}
	if (g_shell->n_up && !g_shell->abort)
		finalize_history();
	g_shell->current->index = (int)ft_strlen(g_shell->current->row);
	g_shell->n_up = 0;
	write(1, "\n", 1);
}
