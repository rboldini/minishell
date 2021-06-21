/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbuonvin <vbuonvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 17:17:33 by vbuonvin          #+#    #+#             */
/*   Updated: 2021/06/21 13:41:35 by rboldini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	process_char(t_option *lista, va_list argptr)
{
	int		len;
	char	temp;

	temp = (char)va_arg(argptr, int);
	len = 1;
	if (lista->width || lista->flag_minus)
	{
		if (lista->flag_minus)
		{
			ft_setup_width(lista, len);
			ft_putchar(temp, lista);
			ft_putstr(lista->output_w, lista);
			free(lista->output_w);
			return ;
		}
		else
		{
			ft_setup_width(lista, len);
			ft_putstr(lista->output_w, lista);
			free(lista->output_w);
			ft_putchar(temp, lista);
			return ;
		}
	}
	ft_putchar(temp, lista);
}
