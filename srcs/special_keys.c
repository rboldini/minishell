#include "../includes/minishell.h"

void	ft_process_delete(t_history *curr)
{
	int	i;
	int	len;

	i = curr->index;
	len = ft_strlen(curr->row);
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
}

void	ft_arrow_ud(/*int x, t_history *curr*/)
{
	/*
	 * UP will duplicate the curr->previous->row to a new row, if it's pressed more
	 * times, without an 'Enter' press, it will free(curr->row) and duplicate the
	 * curr->previous->previous->row(etc..);
	 * Logic: if the user write something and then press UP, we'll store the row
	 * in minishell->tmp->row, just in case he/she would press DOWN to take it back.
	 * In case the 'ENTER' Key is pressed minishell->curr will be sent to the parser.
	 */
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
}

int 	ft_process_backspace(t_history *curr)
{
	int	i;
	int len;

	i = curr->index;
	len = ft_strlen(curr->row);
	// printf("\ncurr->row %s\n", curr->row);
	// printf("curr->index %i\n", curr->index);
	// printf("len %i\n", len);


	if (i > 0 && i < (int)ft_strlen(curr->row))
	{
		write(1, "\b", 1);
		while (i < (int)ft_strlen(curr->row))
		{
			curr->row[i - 1] = curr->row[i];
			//printf("non sono alla fine\n");
			write(1, &curr->row[i - 1], 1);
			i++;
		}
		curr->index--;
		curr->row[ft_strlen(curr->row) - 1] = 0;
		write(1, " \b", 2);
		i = 0;
		while (i <= (int)ft_strlen(curr->row) - curr->index)
		{
			write(1, "\b", 1);
			i++;
		}
		//curr->index--;
	}
	else if (i == (int)ft_strlen(curr->row) && i > 0)
	{
		curr->row[i - 1] = 0;
		//printf("mi trovo alla fine\n");
		write(1, "\b \b", 3);
		curr->index--;
	}
	return (1);
}
