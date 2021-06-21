/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controllo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbuonvin <vbuonvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 10:15:40 by vbuonvin          #+#    #+#             */
/*   Updated: 2021/06/21 13:41:35 by rboldini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_is_type(char c, t_option *lista)
{
	if (c == 'c' || c == 's'
		|| c == 'p' || c == 'i'
		|| c == 'd' || c == 'u'
		|| c == 'x' || c == 'X' || c == '%')
	{
		lista->type = c;
		return (1);
	}
	else
	{
		lista->type = 0;
		return (0);
	}
}

void	ft_control_flag(const char *str, int i, t_option *lista)
{
	lista->flag_minus = 0;
	lista->flag_zero = 0;
	if (str[i] == '-' || str[i + 1] == '-')
		lista->flag_minus = 1;
	if ((str[i] == '0' || str[i + 1] == '0') && str[i] != '.')
		lista->flag_zero = 1;
}

void	ft_control_w(const char *str, int i, t_option *lista, va_list argptr)
{
	int	num;

	lista->width = 0;
	num = lista->width;
	while (str[i] == '-' || str[i] == '0')
		i++;
	if (ft_isdigit(str[i]) || str[i] == '*')
	{
		while (str[i] != '.' && (str[i] == '*' || ft_isdigit(str[i])))
		{
			if (str[i] == '*')
			{
				num = va_arg(argptr, int);
				if (num < 0)
				{
					num *= -1;
					lista->flag_minus = 1;
				}
				break ;
			}
			num = (str[i] - 48) + (num * 10);
			i++;
		}
		lista->width = num;
	}
}

void	ft_control_p(const char *str, int i, t_option *lista, va_list argptr)
{
	int	num;

	num = 0;
	lista->dot = 0;
	lista->precision = -1;
	while (str[i] != '.' && !ft_is_type(str[i], lista))
		i++;
	if (str[i] == '.')
	{
		lista->dot = 1;
		i++;
		while (ft_isdigit(str[i]) || (str[i] == '*' || ft_isdigit(str[i])))
		{
			if (str[i] == '*')
			{
				num = va_arg(argptr, int);
				if (num < 0)
					num = -1;
				break ;
			}
			num = (str[i] - 48) + (num * 10);
			i++;
		}
		lista->precision = num;
	}
}

void	ft_control_type(const char *str, int i, t_option *lista)
{
	int	n;

	n = 1;
	while (!ft_is_type(str[i], lista))
	{
		n++;
		i++;
	}
	lista->arg_i = n;
	if (ft_is_type(str[i], lista))
		lista->type = str[i];
}
