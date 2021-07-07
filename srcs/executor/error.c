#include "../../includes/minishell.h"

void	ft_error(int errnum, char *str, int cmd_flag)
{
	if (cmd_flag == 258)
	{
		g_shell->abort = 1;
		ft_printf_fd(2, "Conchiglia: syntax error\n");
		errno = 258;
	}
	else if (cmd_flag == 139)
	{
		g_shell->abort = 1;
		ft_printf_fd(2, "Segmentation fault: 11\n");
		errno = 139;
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
