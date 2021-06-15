
#include "../../includes/minishell.h"

int	valid_env_decla(char *raw)
{
	int i;

	i = 0;
	while(raw[i])
	{
		if(raw[i] == ' ')
			return (0);
		else if(raw[i] == '=')
			return (1);
		i++;
	}
	return(0);
}

enum e_cmd
{
	CMD_PWD,
	CMD_CD,
	CMD_ENV,
	CMD_EXP,
	CMD_UNSET,
	CMD_ECHO,
	CMD_EXIT,
	CMD_RUN,
	ENV_DECLA,
};

int	check_for_cmd(char *cmd)
{
	if(!ft_strncmp(cmd, "./", 2))
		return (CMD_RUN);			//da rifare
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
	else if(valid_env_decla(cmd))
		return (ENV_DECLA);
	else if(!ft_strcmp(cmd, "exit"))
	{
		ft_printf_fd(1, "exit\n");
		exit(0);
	}
	else
		return (-1);
}

void run_command(int code, t_cmd *cmd, t_env *env)
{
	if(code == CMD_RUN)
		;//run_program();
	else if(code == CMD_CD)
		ft_cd(cmd->len, cmd->arr, &env);
	else if(code == CMD_PWD)
		ft_pwd();
	else if(code == CMD_ECHO)
		ft_echo(cmd->len, cmd->arr);
	else if(code == CMD_UNSET)
		ft_unset(&env, cmd->len, cmd->arr);
	else if(code == CMD_ENV)
		ft_env(env, cmd->len, cmd->arr);
	else if(code == CMD_EXP)
		ft_export(env, cmd->len, cmd->arr);
	else if(code == ENV_DECLA)
		create_new_env(&env, cmd->arr[0], 0);
}

void forker(t_cmd *cmd, t_env *env, int cmd_code)
{
	int fd[2];
	int err;
	int pid;
	t_cmd *tmp;
	int saved_stdout = dup(STDOUT_FILENO);
	int saved_stdin = dup(STDIN_FILENO);

	err = pipe(fd);
	if(err == -1)
		return ;
	if (cmd_code == CMD_RUN)
	{
		pid = fork();
		if(!pid)
		{
			if (cmd->next && cmd->file_out == 1)
				dup2(fd[1], 1);
			if (cmd->file_out != 1)
				dup2(cmd->file_out, 1);
			if (cmd->has_previous && cmd->file_in == 0)
				dup2(fd[0], 0);
			if (cmd->file_in != 0)
				dup2(cmd->file_in, 0);
			run_command(cmd_code, cmd, env);
			if (cmd->file_out != 1)
				close(cmd->file_out);
			if (cmd->file_in != 0)
				close(cmd->file_in);
			cmd = cmd->next;
			/*
			tmp = cmd;
			while(tmp->next && tmp->file_out == 1)
			{
				tmp->file_out = fd[1];
				tmp->next->file_in = fd[0];
				tmp = tmp->next;
			}
			dup2(1, fd[1]);
			dup2(0, fd[0]);
			while (cmd)
			{
				run_command(cmd_code, cmd, env);
				cmd = cmd->next;
			}
			*/
			exit(0); // <-- uscita da processo segnala il riavvio del processo padre
		}
		else
		{
			wait(&pid);
		}
	}
	else
	{
		while (cmd)
		{
			if (cmd->next && cmd->file_out == 1)
				dup2(fd[1], 1);
			if (cmd->file_out != 1)
				dup2(cmd->file_out, 1);
			if (cmd->has_previous && cmd->file_in == 0)
				dup2(fd[0], 0);
			if (cmd->file_in != 0)
				dup2(cmd->file_in, 0);
			run_command(cmd_code, cmd, env);
			if (cmd->file_out != 1)
				close(cmd->file_out);
			if (cmd->file_in != 0)
				close(cmd->file_in);
			cmd = cmd->next;
		}
	}
	close(fd[0]); // <-- ricordarsi di chiudere fd correttamente
	close(fd[1]); // <-- ricordarsi di chiudere fd correttamente
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
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
	//free_cmd_struct();
}
/*
int main(void)
{
	return (1);
}
*/
/*

->/usr/local/bin
->/usr/bin
->/bin
->/usr/sbin
->/sbin
->/usr/local/munki

*/
