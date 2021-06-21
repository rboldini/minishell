/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbuonvin <vbuonvin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 13:24:04 by vbuonvin          #+#    #+#             */
/*   Updated: 2021/06/21 13:41:35 by rboldini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_l;
	t_list	*tmp;

	if (!lst)
		return (NULL);
	new_l = ft_lstnew(f(lst->content));
	if (!new_l)
		return (NULL);
	tmp = new_l;
	lst = lst->next;
	while (lst)
	{
		new_l->next = ft_lstnew(f(lst->content));
		if (!new_l->next)
		{
			ft_lstclear(&tmp, del);
			return (NULL);
		}
		new_l = new_l->next;
		lst = lst->next;
	}
	return (tmp);
}
