#include "../../includes/minishell.h"

void	ctrl_left(t_history *curr, int i)
{
	if (curr->index > 0 && ft_isalnum(curr->row[i])
		&& (!(ft_isalnum(curr->row[i - 1]))))
	{
		curr->index--;
		i--;
		write(1, "\b", 1);
	}
	while (curr->index > 0 && !(ft_isalnum(curr->row[i])
			&& !ft_isalnum(curr->row[i - 1])))
	{
		i--;
		curr->index--;
		write(1, "\b", 2);
	}
}

void	ft_move_word2(t_history *curr, int i)
{
	if (curr->index == 0 && ft_strlen(curr->row))
	{
		curr->index++;
		write(1, "\033[C", 3);
		i++;
	}
	if (curr->index < (int)ft_strlen(curr->row)
		&& !ft_isalnum(curr->row[i]) && ft_isalnum(curr->row[i - 1]))
	{
		curr->index++;
		i++;
		write(1, "\033[C", 3);
	}
}

void	ft_move_word(int c, t_history *curr)
{
	int	i;

	i = curr->index;
	if (c == 68)
		ctrl_left(curr, i);
	else
	{
		ft_move_word2(curr, i);
		while (curr->index < (int)ft_strlen(curr->row)
			&& !(!ft_isalnum(curr->row[i]) && ft_isalnum(curr->row[i - 1])))
		{
			i++;
			curr->index++;
			write(1, "\033[C", 3);
		}
	}
}

int	ft_check_ctrl(int *c)
{
	*c = ft_hook_char();
	if (*c == 59)
	{
		*c = ft_hook_char();
		if (*c == 53)
		{
			*c = ft_hook_char();
			if (*c == 68 || *c == 67)
				return (1);
		}
	}
	return (0);
}
