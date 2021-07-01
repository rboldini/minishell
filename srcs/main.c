#include <stdio.h>
#include "../includes/minishell.h"

void	watermark(void)
{
	printf("\n" CC_BHYEL
		   "███╗   ███╗██████╗      ███████╗██╗  ██╗███████╗██╗     ██╗"
		"          _.---._		\n"
		   "████╗ ████║██╔══██╗     ██╔════╝██║  ██║██╔════╝██║     ██║"
		"      .\'\"\".\'/|\\`.\"\"\'.\n"
		   "██╔████╔██║███████║     ███████╗███████║█████╗  ██║     ██║"
		"     :  .' / | \\ `.  :	\n"
		   "██║╚██╔╝██║██╔══██╗     ╚════██║██╔══██║██╔══╝  ██║     ██║"
		"     '.'  /  |  \\  `.'	\n"
		   "██║ ╚═╝ ██║██║   ██╗██╗ ███████║██║  ██║███████╗███████╗███"
		"████╗ `. /   |   \\ .'	\n"
		   "╚═╝     ╚═╝╚═╝   ╚═╝╚═╝ ╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══"
		"════╝   `-.__|__.-'		\n"
		   CC_WHT "\t\t\t\t\t   Fatto da " CC_CYN "tutti"\
CC_WHT " & " CC_CYN "nessuno" CC_RESET "\n");
}

void	init_minishell(char **envp)
{
	minishell = ft_calloc(1, sizeof(t_shell));
	ft_memset((minishell), 0, sizeof(t_shell));
	(minishell)->current = NULL;
	ft_new_history(&(minishell)->current);
	(minishell)->current->index = 0;
	(minishell)->n_up = 0;
	minishell->prompt = calloc(0, 1);
	minishell->env = init_env(envp);
	edit_env(&minishell->env, "OLDPWD", ft_getenv(minishell->env, "PWD"));
}

void	shell(t_cmd **cmd_arr, t_cmd *cmd, int arr_i)
{
	minishell->pid = 0;
	set_prompt("\e[1;35mCONCHIGLIA -> % \e[0m");
	if (!minishell->abort_dred)
		get_prompt();
	ft_hook_signal();
	if (!minishell->abort_dred)
	{
		minishell->abort = 0;
		minishell->in_dred = 0;
		hook_line(minishell);
	}
	minishell->abort = 0;
	minishell->abort_dred = 0;
	minishell->in_dred = 0;
	cmd_arr = start_parsing(minishell->current->row);
	arr_i = 0;
	while (*(cmd_arr + arr_i))
	{
		cmd = *(cmd_arr + arr_i);
		if (cmd->len)
			ft_executor(cmd, minishell->env);
		arr_i++;
	}
	free(cmd_arr);
}

int	main(int n, char **arg, char **envp)
{
	t_cmd	**cmd_arr;
	t_cmd	*cmd;
	int		arr_i;

	(void)n;
	(void)arg;
	arr_i = 0;
	cmd_arr = 0;
	cmd = 0;
	watermark();
	init_minishell(envp);
	while (1)
	{
		shell(cmd_arr, cmd, arr_i);
		if (ft_strlen(minishell->current->row) && !minishell->abort_dred)
			ft_new_history(&minishell->current);
	}
	return (0);
}
