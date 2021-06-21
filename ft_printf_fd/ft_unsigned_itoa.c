/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_itoa.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbuonvin <vbuonvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 10:50:07 by vbuonvin          #+#    #+#             */
/*   Updated: 2021/06/21 13:41:35 by rboldini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_unsigned_nblen(unsigned int n)
{
	int	slen;

	slen = 1;
	while (slen < 10)
	{
		if (ft_isdigit(n + '0'))
			break ;
		n = n / 10;
		slen++;
	}
	return (slen);
}

char	*ft_unsigned_converter(unsigned int n, char *newstring, int slen)
{
	newstring[slen] = '\0';
	slen--;
	while (slen >= 0)
	{
		newstring[slen] = (n % 10) + 48;
		n = n / 10;
		slen--;
	}
	return (newstring);
}

char	*ft_unsigned_itoa(unsigned int n)
{
	int		slen;
	char	*newstring;

	slen = ft_unsigned_nblen(n);
	newstring = (char *)ft_calloc(sizeof(char), slen + 1);
	if (newstring == NULL)
		return (NULL);
	return (ft_unsigned_converter(n, newstring, slen));
}
