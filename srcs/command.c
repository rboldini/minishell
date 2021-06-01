#include "../includes/minishell.h"
#include <string.h>

void set_prompt(t_shell *minishell, char *str)
{
	if (minishell->prompt != NULL)
		free(minishell->prompt);

	minishell->prompt = malloc(strlen(str) + 1);
	strcpy(minishell->prompt, str);
}

char* getprompt(t_shell *minishell)
{
	return minishell->prompt;
}

//void	command_handle(char *command, t_shell *minishell)
//{
//	if (!ft_strcmp(command, CMD_ECHO))
//		ft_echo(minishell);
//	else if (!ft_strcmp(command, EXIT))
//	{
//		free(minishell->line);
//		free(minishell);
//		exit(0);
//	}
//	else if (!ft_strcmp(command, PWD))
//		ft_pwd(minishell);
//	else if (!ft_strcmp(command, CD))
//		ft_cd(minishell);
//	else
//	{
//		printf(CC_MAG"%s:"CC_RESET, "TEST");
//		printf(CC_RED" command not found: %s\n"CC_RESET, minishell->splitted[0]);
//	}
//}