#include "../../includes/minishell.h"

void	set_prompt(char *str)
{
	if (g_shell->prompt)
		free(g_shell->prompt);
	g_shell->prompt = malloc(ft_strlen(str) + 1);
	strcpy(g_shell->prompt, str);
}

void	get_prompt(void)
{
	write(1, g_shell->prompt, ft_strlen(g_shell->prompt));
}

void	run_command(int code, t_cmd *cmd, t_env *env)
{
	if (code == CMD_CD)
		ft_cd(cmd->len, cmd->arr, &env);
	else if (code == CMD_PWD)
		ft_pwd();
	else if (code == CMD_ECHO)
		ft_echo(cmd->len, cmd->arr);
	else if (code == CMD_UNSET)
		ft_unset(&env, cmd->len, cmd->arr);
	else if (code == CMD_ENV)
		ft_env(env, cmd->len, cmd->arr);
	else if (code == CMD_EXP)
		ft_export(env, cmd->len, cmd->arr);
	else if (code == ENV_DECLA)
		create_new_env(&env, cmd->arr[0], 0);
}
