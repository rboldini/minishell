#include <stdio.h>
#include "../includes/minishell.h"
#include "../includes/color.h"

void	watermark(void)
{
	//printf("%c[1;1H%c[2J", 27, 27);
	printf("\n" CC_BHYEL

		   "███╗   ███╗██████╗      ███████╗██╗  ██╗███████╗██╗     ██╗          _.---._		\n"
		   "████╗ ████║██╔══██╗     ██╔════╝██║  ██║██╔════╝██║     ██║      .\'\"\".\'/|\\`.\"\"\'.\n"
		   "██╔████╔██║███████║     ███████╗███████║█████╗  ██║     ██║     :  .' / | \\ `.  :	\n"
	 	   "██║╚██╔╝██║██╔══██╗     ╚════██║██╔══██║██╔══╝  ██║     ██║     '.'  /  |  \\  `.'	\n"
		   "██║ ╚═╝ ██║██║   ██╗██╗ ███████║██║  ██║███████╗███████╗███████╗ `. /   |   \\ .'	\n"
		   "╚═╝     ╚═╝╚═╝   ╚═╝╚═╝ ╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝   `-.__|__.-'		\n"
		   CC_WHT "\t\t\t\t\t   Fatto da " CC_CYN "tutti"\
CC_WHT " & " CC_CYN "nessuno" CC_RESET "\n");
}

void	init_minishell()
{
	minishell = ft_calloc(1, sizeof(t_shell));
	ft_memset((minishell), 0, sizeof(t_shell));
	(minishell)->current = NULL;
	ft_new_history(&(minishell)->current);
	(minishell)->current->index = 0;
	(minishell)->n_up = 0;
	(minishell)->n_down = 0;
}


void	free_history(t_history *curr)
{
	while(curr->prev)
	{
		free(curr->row);
		curr = curr->prev;
		free(curr->next);
	}
	free(curr->row);
	free(curr);
}

int main(int n, char **arg, char **envp)

{
	t_cmd	**cmd_arr;
	t_cmd	*cmd;
	int	arr_i;

	(void)n;
	(void)arg;
	watermark();
	init_minishell();
	minishell->prompt = calloc(0, 1);
	minishell->env = init_env(envp);
	while (1)
	{
		set_prompt(minishell, "\e[1;35mCONCHIGLIA -> % \e[0m");
		write (1, minishell->prompt, ft_strlen(minishell->prompt));
		ft_hook_signal();
		hook_line(minishell);
		cmd_arr = start_parsing(minishell->current->row);
		arr_i = 0;
		while (*(cmd_arr + arr_i))
		{
			cmd = *(cmd_arr + arr_i);
			if (cmd->len)
				ft_executor(cmd, minishell->env);
			arr_i++;
		}
		if (ft_strlen(minishell->current->row))
			ft_new_history(&minishell->current);
	}
	return (0);
}
