/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbuonvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 10:12:55 by vbuonvin          #+#    #+#             */
/*   Updated: 2021/06/21 13:41:35 by rboldini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*a_str;

	if (!s)
		return (NULL);
	i = 0;
	a_str = (char *)ft_calloc(sizeof(char), ft_strlen(s) + 1);
	if (!a_str)
		return (NULL);
	while (s[i])
	{
		a_str[i] = f(i, s[i]);
		i++;
	}
	return (a_str);
}
