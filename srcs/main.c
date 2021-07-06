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

void	init_abort(void)
{
	g_shell->abort = 0;
	g_shell->abort_dred = 0;
	g_shell->in_dred = 0;
}

void	init_g_shell(char **envp)
{
	g_shell = ft_calloc(1, sizeof(t_shell));
	ft_memset((g_shell), 0, sizeof(t_shell));
	(g_shell)->current = NULL;
	ft_new_history(&(g_shell)->current);
	(g_shell)->current->index = 0;
	(g_shell)->n_up = 0;
	g_shell->prompt = calloc(0, 1);
	g_shell->env = init_env(envp);
	init_abort();
	edit_env(&g_shell->env, "OLDPWD", ft_getenv(g_shell->env, "PWD"));
}

void	shell(t_cmd **cmd_arr, t_cmd *cmd, int arr_i)
{
	t_cmd	*tmp;

	g_shell->pid = 0;
	set_prompt("\e\033[0;32mCON\033[0;37mCHIG\033[0;31mLIA -> \e[0m🤌  ");
	if (!g_shell->abort_dred)
		get_prompt();
	ft_hook_signal();
	if (!g_shell->abort_dred)
	{
		init_abort();
		hook_line(g_shell);
	}
	init_abort();
	if (ft_strlen(g_shell->current->row))
	{
		cmd_arr = start_parsing(g_shell->current->row);
		arr_i = 0;
		while (*(cmd_arr + arr_i) && !g_shell->abort)
		{
			cmd = *(cmd_arr + arr_i);
			if (cmd->len)
				ft_executor(cmd, g_shell->env);
			arr_i++;
		}
		while (cmd)
		{
			ft_free_matrix(cmd->arr);
			if (cmd->file_in != 0)
				close(cmd->file_in);
			if (cmd->file_out != 1)
				close(cmd->file_out);
			free(cmd->eof);
			tmp = cmd;
			cmd = cmd->next;
			free(tmp);
		}
		free(cmd_arr);
	}
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
	init_g_shell(envp);
	while (1)
	{
		shell(cmd_arr, cmd, arr_i);
		if (ft_strlen(g_shell->current->row) && !g_shell->abort_dred)
			ft_new_history(&g_shell->current);
	}
	return (0);
}
