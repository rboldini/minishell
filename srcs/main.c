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

int main()
{
	t_shell *minishell;


	minishell = malloc(sizeof(t_shell));
	watermark();
	minishell->prompt = malloc(0);
	while (1)
	{
		//sig_init();
		set_prompt(minishell, "TEST -> % ");
		printf(CC_BMAG"%s"CC_RESET, getprompt(minishell));
		//printf("%d", '[');
		fflush(stdout);
		lexar(minishell);
		//command_handle(minishell->splitted[0], minishell);
		//printf("%s", minishell->line);
	}
	exit (0);
}
