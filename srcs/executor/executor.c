
#include "../../includes/minishell.h"

char *is_exec(t_env *env, int ac, char  **av)
{
	char	**paths;
	char	*tmp;
	char	*join;
	char	*slash;
	int		i;

	(void)ac;
	if (!av[0])
		return (0);
	i = 0;
	tmp = ft_getenv(env, "PATH");
	paths = ft_split(tmp, ':');
	if (ft_isdir(av[0]))
	{
		ft_free_matrix(paths);
		return (av[0]);
	}
	else
	{
		while (paths[i])
		{
			slash = ft_strjoin("/", av[0]);
			join = ft_strjoin(paths[i], slash);
			if (ft_isfile(join))
			{
				free(slash);
				ft_free_matrix(paths);
				return (join);
			}
			free(slash);
			free(join);
			i++;
		}
		ft_error(errno, av[0], 1);
	}
	ft_free_matrix(paths);
	return (NULL);
}

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

int	check_for_cmd(char *cmd)
{
	if (!cmd)
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
	else if(valid_env_decla(cmd))
		return (ENV_DECLA);
	else if(!ft_strcmp(cmd, "exit"))
	{
		ft_exit(minishell);
		return (0);
	}
	else
		return (CMD_RUN);
}

void forker(t_cmd *cmd, t_env *env, int cmd_code)
{
	int fd[2];
	int err;
	int saved_stdout = dup(STDOUT_FILENO);
	int saved_stdin = dup(STDIN_FILENO);
	int	status;
	char *path;

	fd[0] = 0;
	fd[1] = 0;
	err = pipe(fd);
	if(err == -1)
	{
		printf("ERROR CREATING PIPPA\n");
		return ;
	}
	if (cmd->next && cmd->file_out == 1 && cmd->next->file_in == 0)
	{
		cmd->file_out = fd[1];
		cmd->next->file_in = fd[0];
	}
	if (cmd_code == CMD_RUN)
	{
		path = is_exec(env, cmd->len, cmd->arr);
		if(path)
		{	
			minishell->pid = fork();
			if(!minishell->pid)
			{
				dup2(cmd->file_in, STDIN_FILENO);
				dup2(cmd->file_out, STDOUT_FILENO);
				ft_runner(env, cmd->len, cmd->arr); //dovrebbe bastare sostituire a ft_runner direttamente execve dandogli path come var perchè adesso i controlli li facciamo fuori dal fork
				if (cmd->file_out != 1)
					close(cmd->file_out);
				if (cmd->file_in != 0)
					close(cmd->file_in);
				free(path);
				exit(0);
			}
			else
			{
				waitpid(minishell->pid, &status, WUNTRACED|WCONTINUED);
				if (cmd->file_out != 1)
					close(cmd->file_out);
				if (cmd->file_in != 0)
					close(cmd->file_in);
			}
			free(path);
		}
	}
	else
	{
		dup2(cmd->file_in, 0);
		dup2(cmd->file_out, 1);
		if (cmd->next && cmd->file_out == 1 && cmd->next->file_in == 0)
		{
			err = pipe(fd);
			cmd->file_out = fd[1];
			cmd->next->file_in = fd[0];
		}
		run_command(cmd_code, cmd, env);
		if (cmd->file_out != 1)
		{
			close(cmd->file_out);
			dup2(saved_stdout, STDOUT_FILENO);
		}
		if (cmd->file_in != 0)
		{
			close(cmd->file_in);
			dup2(saved_stdin, STDIN_FILENO);
		}
	}
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
}

void	ft_executor(t_cmd *cmd, t_env *env)
{
	t_cmd *tmp;
	int cmd_code;

	tmp = cmd;
	cmd_code = -1;
	while (tmp)
	{
		cmd_code = check_for_cmd(tmp->arr[0]);
		if(cmd_code == -1 && tmp->arr[0])
		{
			ft_printf_fd(1, "%s: command not found\n", tmp->arr[0]);
			break ;
		}
		forker(tmp, env, cmd_code);
		tmp = tmp->next;
	}
	while (cmd)
	{
		ft_free_matrix(cmd->arr);
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
}
