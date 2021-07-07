#include "../../includes/minishell.h"

char	*elab_joined(char **av, char **paths)
{
	char	*slash;
	char	*join;
	int		i;

	i = 0;
	while (paths[i])
	{
		slash = ft_strjoin("/", av[0]);
		join = ft_strjoin(paths[i], slash);
		if (ft_isfile(join))
		{
			free(slash);
			return (join);
		}
		free(slash);
		free(join);
		i++;
	}
	return (NULL);
}

char	*is_exec(t_env *env, int ac, char **av)
{
	char	**paths;
	char	*tmp;
	char	*join;

	(void)ac;
	if (!av[0])
		return (0);
	tmp = ft_getenv(env, "PATH");
	if (!tmp)
	{
		ft_error(errno, av[0], 1);
		return (NULL);
	}
	paths = ft_split(tmp, ':');
	join = return_exec(tmp, av, paths);
	ft_free_matrix(paths);
	return (join);
}

int	valid_env_decla(char *raw)
{
	int	i;

	i = 0;
	while (raw[i])
	{
		if (raw[i] == ' ')
			return (0);
		else if (raw[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	check_for_cmd(char *cmd)
{
	if (!cmd)
		return (CMD_RUN);
	else if (!ft_strcmp(cmd, "cd"))
		return (CMD_CD);
	else if (!ft_strcmp(cmd, "pwd"))
		return (CMD_PWD);
	else if (!ft_strcmp(cmd, "echo"))
		return (CMD_ECHO);
	else if (!ft_strcmp(cmd, "unset"))
		return (CMD_UNSET);
	else if (!ft_strcmp(cmd, "env"))
		return (CMD_ENV);
	else if (!ft_strcmp(cmd, "export"))
		return (CMD_EXP);
	else if (valid_env_decla(cmd))
		return (ENV_DECLA);
	else if (!ft_strcmp(cmd, "exit"))
	{
		ft_exit(g_shell);
		return (0);
	}
	else
		return (CMD_RUN);
}

void	ft_executor(t_cmd *cmd, t_env *env)
{
	t_cmd	*tmp;
	int		cmd_code;

	tmp = cmd;
	while (tmp)
	{
		cmd_code = check_for_cmd(tmp->arr[0]);
		if (!ft_strcmp(tmp->arr[0], "./minishell"))
			ft_hook_fake_signal();
		forker(tmp, env, cmd_code);
		tmp = tmp->next;
		if (g_shell->abort)
			break ;
	}
}
