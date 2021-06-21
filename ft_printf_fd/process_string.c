/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbuonvin <vbuonvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 17:20:15 by vbuonvin          #+#    #+#             */
/*   Updated: 2021/06/21 13:41:35 by rboldini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	string_with_minus(t_option *lista, int len, char *temp)
{
	if (lista->precision > -1)
	{
		ft_setup_precision(lista, len, temp);
		ft_putstr(lista->output_p, lista);
		free(lista->output_p);
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

static void	string_no_minus(t_option *lista, int len, char *temp)
{
	if (lista->precision > -1)
		ft_setup_precision(lista, len, temp);
	if (lista->width)
	{
		ft_setup_width(lista, len);
		ft_putstr(lista->output_w, lista);
		free(lista->output_w);
	}
	if (lista->precision > -1)
	{
		ft_putstr(lista->output_p, lista);
		free(lista->output_p);
	}
	else
		ft_putstr(temp, lista);
}

void	process_string(t_option *lista, va_list argptr)
{
	int		len;
	char	*temp;

	temp = va_arg(argptr, char *);
	if (temp == NULL)
		temp = "(null)";
	len = ft_strlen(temp);
	if (lista->flag_minus)
		string_with_minus(lista, len, temp);
	else
		string_no_minus(lista, len, temp);
}
