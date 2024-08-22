/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpancorb <jpancorb@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 20:15:11 by jpancorb          #+#    #+#             */
/*   Updated: 2024/03/04 19:39:25 by jpancorb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*sft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

static void	sft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
}

static t_list	*sft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

static void	sft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*back;

	back = sft_lstlast(*lst);
	if (!back)
		*lst = new;
	else
		back->next = new;
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	void	*set;

	new_list = NULL;
	while (lst)
	{
		set = f(lst->content);
		new_node = sft_lstnew(set);
		if (!new_node)
		{
			del(set);
			sft_lstclear(&new_list, (*del));
			return (new_list);
		}
		sft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}
