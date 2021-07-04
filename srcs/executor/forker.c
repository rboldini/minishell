#include "../../includes/minishell.h"

void	init_forker(t_forker *forker)
{
	forker->saved_stdin = dup(STDIN_FILENO);
	forker->saved_stdout = dup(STDOUT_FILENO);
	forker->fd[0] = 0;
	forker->fd[1] = 0;
	forker->err = pipe(forker->fd);
	if (forker->err == -1)
	{
		ft_error(errno, "pipe", 0);
		restore_fd(forker);
		return ;
	}
}

int	init_double_readirect(t_forker *forker, t_cmd *cmd)
{
	forker->fd_double[0] = 0;
	forker->fd_double[1] = 0;
	forker->derr = pipe(forker->fd_double);
	(void)forker->derr;
	if (!ft_strlen(cmd->eof))
	{
		ft_printf_fd(2, "Conchiglia: syntax error near unexpected token\n");
		restore_fd(forker);
		g_shell->abort = 1;
		errno = 258;
		return (0);
	}
	forker->inp = d_redirect(cmd->eof);
	if (g_shell->abort_dred)
		return (0);
	cmd->file_in = forker->fd_double[0];
	write(forker->fd_double[1], forker->inp, ft_strlen(forker->inp));
	close(forker->fd_double[1]);
	free(forker->inp);
	return (1);
}

void	not_builtin(t_env *env, t_forker *forker, t_cmd *cmd)
{
	if (forker->path)
	{	
		g_shell->pid = fork();
		if (!g_shell->pid)
		{
			dup2(cmd->file_in, STDIN_FILENO);
			dup2(cmd->file_out, STDOUT_FILENO);
			ft_runner(env, cmd->arr, forker->path);
			if (cmd->file_out != 1)
				close(cmd->file_out);
			if (cmd->file_in != 0)
				close(cmd->file_in);
			free(forker->path);
			exit(0);
		}
		else
		{
			waitpid(g_shell->pid, &forker->status, WUNTRACED | WCONTINUED);
			if (cmd->file_out != 1)
				close(cmd->file_out);
			if (cmd->file_in != 0)
				close(cmd->file_in);
		}
		free(forker->path);
	}
}

void	is_builtin(t_env *env, t_forker *forker, t_cmd *cmd, int cmd_code)
{
	dup2(cmd->file_in, 0);
	dup2(cmd->file_out, 1);
	if (cmd->next && cmd->file_out == 1 && cmd->next->file_in == 0)
	{
		forker->err = pipe(forker->fd);
		cmd->file_out = forker->fd[1];
		cmd->next->file_in = forker->fd[0];
	}
	run_command(cmd_code, cmd, env);
	if (cmd->file_out != 1)
		close(cmd->file_out);
	if (cmd->file_in != 0)
		close(cmd->file_in);
}

void	forker(t_cmd *cmd, t_env *env, int cmd_code)
{
	t_forker	*forker;

	forker = malloc(sizeof(t_forker));
	init_forker(forker);
	if (forker->err == -1)
		return ;
	if (cmd->has_dred)
		if (!init_double_readirect(forker, cmd))
			return ;
	if (cmd->next && cmd->file_out == 1 && cmd->next->file_in == 0)
	{
		cmd->file_out = forker->fd[1];
		cmd->next->file_in = forker->fd[0];
	}
	if (cmd_code == CMD_RUN)
	{
		forker->path = is_exec(env, cmd->len, cmd->arr);
		not_builtin(env, forker, cmd);
	}
	else
		is_builtin(env, forker, cmd, cmd_code);
	restore_fd(forker);
	free(forker);
}
