#include "../../includes/minishell.h"

void	restore_fd(t_forker *forker)
{
	dup2(forker->saved_stdout, STDOUT_FILENO);
	dup2(forker->saved_stdin, STDIN_FILENO);
	close(forker->saved_stdout);
	close(forker->saved_stdin);
}
