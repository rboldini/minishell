/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_pointer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbuonvin <vbuonvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 17:32:29 by vbuonvin          #+#    #+#             */
/*   Updated: 2021/06/21 13:41:35 by rboldini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	pointer_with_min(t_option *lista, int len, char *temp, size_t addr)
{
	if (addr == 0 && !lista->precision)
	{
		len = 2;
		ft_putstr("0x", lista);
	}
	else
		ft_putstr(temp, lista);
	if (lista->width)
	{
		ft_setup_width(lista, len);
		ft_putstr(lista->output_w, lista);
		free(lista->output_w);
	}
}

static void	pointer_no_min(t_option *lista, int len, char *temp, size_t addr)
{
	if (lista->width)
	{
		if (addr == 0 && !lista->precision)
			len = 2;
		ft_setup_width(lista, len);
		ft_putstr(lista->output_w, lista);
		free(lista->output_w);
	}
	if (addr == 0 && !lista->precision)
		ft_putstr("0x", lista);
	else
		ft_putstr(temp, lista);
}

void	process_pointer(t_option *lista, va_list argptr)
{
	size_t	addr;
	int		len;
	char	*temp;

	addr = va_arg(argptr, size_t);
	temp = ft_address_converter(addr);
	len = ft_strlen(temp);
	if (lista->flag_minus)
		pointer_with_min(lista, len, temp, addr);
	else
		pointer_no_min(lista, len, temp, addr);
	if (temp != NULL)
		free(temp);
	temp = NULL;
}
