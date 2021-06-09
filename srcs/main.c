#include <stdio.h>
#include "../includes/minishell.h"
#include "../includes/color.h"

void	watermark(void)
{
	//printf("%c[1;1H%c[2J", 27, 27);
	printf("\n" CC_BHYEL
		   "███╗   ███╗██████╗      ███████╗██╗  ██╗███████╗██╗     ██╗                   _.---._		\n"
		   "████╗ ████║██╔══██╗     ██╔════╝██║  ██║██╔════╝██║     ██║               .\'\"\".\'/|\\`.\"\"\'.	\n"
		   "██╔████╔██║███████║     ███████╗███████║█████╗  ██║     ██║              :  .' / | \\ `.  :	\n"
	 	   "██║╚██╔╝██║██╔══██╗     ╚════██║██╔══██║██╔══╝  ██║     ██║              '.'  /  |  \\  `.'	\n"
		   "██║ ╚═╝ ██║██║   ██╗██╗ ███████║██║  ██║███████╗███████╗███████╗          `. /   |   \\ .'	\n"
		   "╚═╝     ╚═╝╚═╝   ╚═╝╚═╝ ╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝            `-.__|__.-'		\n"
		   CC_WHT "\t\t\t\t\t   Fatto da " CC_CYN "tutti"\
CC_WHT " & " CC_CYN "nessuno" CC_RESET "\n");
}

void	init_minishell(t_shell **minishell)
{
	*minishell = malloc(sizeof(t_shell));
	(*minishell)->current = NULL;
	(*minishell)->tmp = malloc(sizeof(t_shell));
	ft_new_history(&(*minishell)->current);
	(*minishell)->current->index = 0;
	(*minishell)->n_up = 0;
	(*minishell)->n_down = 0;
}

int main(int n, char **arg, char **envp)
{
	t_shell *minishell;
	t_env	*enva;
	t_cmd	**cmd_arr;
	t_cmd	*cmd;
	//int i = 0;

	(void)n;
	(void)arg;
	watermark();
	init_minishell(&minishell);
	minishell->prompt = malloc(0);
	enva = init_env(envp);
	//create_new_env(&enva, "GIOVANNI=ciao ciao ciao", 1);
	//unset_env(&enva, "GIOVANNI");
	//create_new_env(&enva, "GIOVANNI=uhuhuh", 1);
	//set_env(&enva, "GIOVANNI");
	//printf("%s\n", ft_getenv(enva, "LOGNAME"));
	//ft_env(enva);
	while (1)
	{
		set_prompt(minishell, "\e[1;35mCONCHIGLIA -> % \e[0m");
		write (1, minishell->prompt, ft_strlen(minishell->prompt));
		fflush(stdout);
		hook_line(minishell);
		cmd_arr = start_parsing(minishell->current->row);
		while (*cmd_arr)
		{
			cmd = *cmd_arr;
			while (cmd)
			{
				if (cmd->len)
					printf("%s\n", cmd->arr[0]);
				printf("file in: %d file out: %d is app: %d\n", cmd->file_in, cmd->file_out, cmd->is_append);

				if (cmd->len)
					ft_executor(cmd, enva);
				cmd = cmd->next;
			}
			cmd_arr++;
		}
		if (ft_strlen(minishell->current->row))
			ft_new_history(&minishell->current);
	}
	exit (0);
}
