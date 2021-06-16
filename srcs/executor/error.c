#include "../../includes/minishell.h"

void	ft_error(int errnum, char *str)
{
	if (str)
		ft_printf_fd(2, "Conchiglia: %s: %s\n", str, strerror(errnum));
	else
		ft_printf_fd(2, "Conchiglia: %s\n", strerror(errnum));
	return ;
}