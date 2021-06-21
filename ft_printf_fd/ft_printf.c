/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbuonvin <vbuonvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 10:05:45 by vbuonvin          #+#    #+#             */
/*   Updated: 2021/06/21 13:41:35 by rboldini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	setup_struct(t_option *lista)
{
	lista->arg_i = 0;
	lista->width = 0;
	lista->precision = -1;
	lista->dot = 0;
	lista->negative = 0;
	lista->type = 0;
	lista->flag_minus = 0;
	lista->flag_zero = 0;
	lista->h_neg = 0;
	lista->output_p = NULL;
	lista->output_w = NULL;
	lista->output_zeroes = NULL;
}

static void	elab_str(const char *str, int i, va_list argptr, t_option *lista)
{
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			setup_struct(lista);
			ft_controllo(str, i, lista, argptr);
			if (lista->type)
				ft_setup_type(argptr, lista);
			i += lista->arg_i;
		}
		if (str[i] != '%' && str[i] != 0)
		{
			write(1, &str[i], 1);
			lista->return_value++;
			i++;
		}
		if (str[i] == 0)
			break ;
	}
}

int	ft_printf_fd(int fd, const char *str, ...)
{
	int			i;
	va_list		argptr;
	t_option	lista;

	lista.fd = fd;
	lista.return_value = 0;
	i = 0;
	va_start(argptr, str);
	if (!str)
		return (-1);
	elab_str(str, i, argptr, &lista);
	va_end(argptr);
	return (lista.return_value);
}
