#include "../../includes/minishell.h"

void	ft_error(int errnum, char *str, int cmd_flag)
{
	if (cmd_flag == 258)
	{
		ft_printf_fd(2, "Conchiglia: syntax error %s\n", str);
		errno = 258;
		g_shell->abort = 1;
	}
	else if (cmd_flag > 0)
	{
		ft_printf_fd(2, "Conchiglia: %s: command not found\n", str);
		errno = 127;
		g_shell->abort = 1;
	}
	else if (str)
		ft_printf_fd(2, "Conchiglia: %s: %s\n", str, strerror(errnum));
	else
		ft_printf_fd(2, "Conchiglia: %s\n", strerror(errnum));
	return ;
}
