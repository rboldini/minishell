
#include "../includes/minishell.h"

enum e_cmd
{
	CMD_PWD,
	CMD_CD,
	CMD_ENV,
	CMD_EXP,
	CMD_UNSET,
	CMD_ECHO,
	CMD_EXIT,
	CMD_RUN
};

int	check_for_cmd(char *cmd)
{
	if(!ft_strncmp(cmd, "./", 2))
		return (CMD_RUN);
	else if(!ft_strcmp(cmd, "cd"))
		return (CMD_CD);
	else if(!ft_strcmp(cmd, "pwd"))
		return (CMD_PWD);
	else if(!ft_strcmp(cmd, "echo"))
		return (CMD_ECHO);
	else if(!ft_strcmp(cmd, "unset"))
		return (CMD_UNSET);
	else if(!ft_strcmp(cmd, "env"))
		return (CMD_ENV);
	else if(!ft_strcmp(cmd, "export"))
		return (CMD_EXP);
	else if(!ft_strcmp(cmd, "exit"))
	{
		ft_printf_fd(1, "exit\n");
		exit(0);
	}
	else
		return (-1);
}

void forker(t_cmd *cmd, t_env *env, int cmd_code)
{
	int fd[2];
	int err;
	int pid;

	pid = fork();
	if(!pid)
	{
		if(cmd->next && cmd->file_out == 1)
		{
			err = pipe(fd);
			if(err == -1)
				return ;
			cmd->file_out = fd[0];
			cmd->next->file_in = fd[1];
		}
		dup2(stdout, cmd->file_out);
		dup2(stdin, cmd->file_in);
		run_command(cmd_code, cmd, env);
		close(fd); //ricordarsi di chiudere fd
		exit(0);
	}
	else
	{
		wait(pid);
	}
}

void run_command(int code, t_cmd *cmd, t_env *env)
{
	if(code == CMD_RUN)
		run_program();
	else if(code == CMD_CD)
		run_cd();
	else if(code == CMD_PWD)
		run_pwd();
	if(code == CMD_ECHO)
	run_echo(cmd);
	else if(code == CMD_UNSET)
		run_unset();
	else if(code == CMD_ENV)
		run_env();
	else if(code == CMD_EXP)
		run_exp();
}

void	ft_executor(t_cmd *cmd, t_env *env)
{
	t_cmd *tmp;
	int cmd_code;
	int i;

	tmp = cmd;
	i = 0;
	cmd_code = -1;
	while (tmp)
	{
		cmd_code = check_for_cmd(tmp->arr[0]);
		if(cmd_code == -1 && tmp->arr[0])
		{
			ft_printf_fd(1, "%s: command not found\n", tmp->arr[0]);
			return ;
		}
		forker(cmd, env, cmd_code);
		tmp = tmp->next;
	}
	free_cmd_struct();
}

int main(void)
{
	return (1);
}