/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbuonvin <vbuonvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 10:38:48 by vbuonvin          #+#    #+#             */
/*   Updated: 2021/06/21 13:41:35 by rboldini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(char c, t_option *lista)
{
	write(lista->fd, &c, 1);
	lista->return_value++;
}

void	ft_putstr(const char *str, t_option *lista)
{
	int	i;

	i = 0;
	while (str[i])
		ft_putchar(str[i++], lista);
}

unsigned int	count_len(unsigned int n)
{
	unsigned int	len;

	len = 1;
	while (n)
	{
		n /= 16;
		len++;
	}
	return (len);
}

char	*ft_exa_converter(unsigned int n, char c)
{
	int				len;
	char			*converted;

	len = count_len(n);
	converted = (char *)ft_calloc(sizeof(char), (len + 1));
	if (!converted)
		return (0);
	converted[len] = '\0';
	while (len--)
	{
		if (c == 'x')
		{
			converted[len] = "0123456789abcdef"[n % 16];
			n /= 16;
		}
		if (c == 'X')
		{
			converted[len] = "0123456789ABCDEF"[n % 16];
			n /= 16;
		}
	}
	return (converted);
}

char	*ft_address_converter(size_t n)
{
	int		len;
	char	*converted;

	len = count_len(n);
	converted = (char *)ft_calloc(sizeof(char), (len + 3));
	if (!converted)
		return (converted = NULL);
	len += 2;
	converted[len] = '\0';
	while (len--)
	{
		converted[len] = "0123456789abcdef"[n % 16];
		n /= 16;
	}
	converted[1] = 'x';
	converted[0] = '0';
	return (converted);
}
