#include "../../includes/minishell.h"

void	ft_error(int errnum)
{
	ft_printf_fd(2, "Error: %s\n", strerror(errnum));
	return ;
}