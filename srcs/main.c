#include <stdio.h>
#include "../includes/minishell.h"
#include "../includes/color.h"

void	watermark(void)
{
	//printf("%c[1;1H%c[2J", 27, 27);
	printf("\n" CC_BHYEL
		   "███╗   ███╗██████╗      ███████╗██╗  ██╗███████╗██╗     ██╗     \n"
		   "████╗ ████║██╔══██╗     ██╔════╝██║  ██║██╔════╝██║     ██║     \n"
		   "██╔████╔██║███████║     ███████╗███████║█████╗  ██║     ██║     \n"
	 	   "██║╚██╔╝██║██╔══██╗     ╚════██║██╔══██║██╔══╝  ██║     ██║     \n"
		   "██║ ╚═╝ ██║██║   ██╗██╗ ███████║██║  ██║███████╗███████╗███████╗\n"
		   "╚═╝     ╚═╝╚═╝   ╚═╝╚═╝ ╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n"
		   CC_WHT "\t\t\t\t\t   Made by " CC_CYN "rboldini"\
CC_WHT " and " CC_CYN "smenna" CC_RESET "\n");
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
	//int i = 0;

	(void)n;
	(void)arg;
	watermark();
	init_minishell(&minishell);
	minishell->prompt = malloc(0);
	enva = init_env(envp);
	create_new_env(&enva, "GIOVANNI=ciao ciao ciao", 1);
	unset_env(&enva, "GIOVANNI");
	create_new_env(&enva, "GIOVANNI=uhuhuh", 1);
	set_env(&enva, "GIOVANNI");
	printf("%s\n", ft_getenv(enva, "LOGNAME"));

	ft_env(enva);
	while (1)
	{
		set_prompt(minishell, "\e[1;35mTEST -> % \e[0m");
		write (1, minishell->prompt, ft_strlen(minishell->prompt));
		fflush(stdout);
		hook_line(minishell);
		start_parsing(minishell->current->prev->row);
	}
	exit (0);
}
