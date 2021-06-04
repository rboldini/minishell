#include "../includes/minishell.h"

void	ft_process_delete()
{
	/*
	 * just check if here is something to delete at cursor posix, if not
	 * reproduce the bell sound.
	 * Else delete writing ' '.
	 */
}

void	ft_arrow_ud()
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

void	ft_arrow_lr()
{	
	/*
	 *	I know they are actually BONUS but without them debug it's a mess.
	 *	Let it to me. Or do it for fun.
	 *	Behavior is mixed from delete and backspace control for end_line
	 *	or beginning of the line. Work on it with minishell->curr->index.
	 *	HINT: Do we prefer to rename index to posix?
	 */
}

int 	ft_process_backspace(char c, t_shell *minishell)
{
	if (c == 127)
	{
		if (minishell->current->index > (int)ft_strlen(minishell->prompt))
		{
			minishell->current->row[minishell->current->index - 1] = '\0';
			minishell->current->index--;
			printf("\b \b");
			fflush(stdout);
			return (0);
		}
		//TODO: check if before cursor posix is something to delete, if not reproduce the bell sound.
	}
	return (1);
}
