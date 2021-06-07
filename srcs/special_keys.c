#include "../includes/minishell.h"

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

/*
		if (minishell->current->prev) //se esiste un precedente
		{
			element = malloc(sizeof(t_history));
			if (!element)
				exit (-1);
			ft_memcpy(element, minishell->current->prev, sizeof(t_history)); //copia il precedente dentro element 
			free_tmp = element;
			if (ft_strlen(minishell->current->row) && minishell->n_up == 0) //se ho scritto qualcosa e non ho premuto freccia su
			{
				minishell->tmp->row = minishell->current->row; //assegna a tmp il valore di ció che stavamo scrivendo e anche l'indice
				minishell->tmp->index = minishell->current->index;
			}
			write (1, "\r\033[2K", 5); //il cursore torna alla fine
			write (1, minishell->prompt, ft_strlen(minishell->prompt)); //???
			while (element->prev && i++ < minishell->n_up)
				element = element->prev;
			minishell->current->row = ft_strdup(element->row);
			minishell->current->index = (int) ft_strlen(minishell->current->row);
			write (1, minishell->current->row, ft_strlen(minishell->current->row));
			minishell->n_up++;
			free(free_tmp);
		}
*/


void	ft_arrow_ud(int x, t_shell *minishell)
{
	if (x == 65)
	{
		if (minishell->current->prev)
		{
		//	printf("sono qui\n");
			if (ft_strlen(minishell->current->row) && minishell->n_up == 0)
				minishell->tmp = minishell->current;
			write(1, "\r\033[2K", 5);
			write(1, minishell->prompt, ft_strlen(minishell->prompt));
			//while (minishell->current->prev && i++ < minishell->n_up)
			minishell->current = minishell->current->prev;
		//	printf("%s\n", minishell->current->row);
			write(1, minishell->current->row, ft_strlen(minishell->current->row));
			minishell->n_up++;
		}
	}
	// else
	// {
	// 	if (minishell->current->next)
	// 		printf("\n%s", minishell->current->next->row);
	// 	fflush(stdout);
	// }
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
