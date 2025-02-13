/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_remover.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 03:37:57 by sprodatu          #+#    #+#             */
/*   Updated: 2024/07/28 15:38:19 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/garbage_collector.h"

void	free_node(t_garb_node *node)
{
	if (!node)
		return ;
	if (GARBAGE_DEBUG)
		printf("Freeing node at %p\n", (void *)node);
	free(node);
	node = NULL;
}

void	free_garbage(t_garbage *garb_col)
{
	t_garb_node	*current;
	t_garb_node	*next;

	if (!garb_col)
		return ;
	if (garb_col->length == 0)
		return ;
	current = garb_col->tail;
	while (current)
	{
		next = current->prev;
		garb_col->length--;
		if (current->ptr_data != NULL && current->ptr_data != garb_col)
			free_node(current->ptr_data);
		free_node(current);
		current = next;
	}
	free(garb_col);
	return ;
}

int	err_msg(t_garbage *garb_col, char *msg, int ret)
{
	if (!msg)
		return (ret);
	printf("%s\n", msg);
	free_garbage(garb_col);
	exit(ret);
	return (ret);
}

// void	free_specific_alloc(t_garbage *garb_col, void *ptr)
// {
// 	t_garb_node	*current;
// 	t_garb_node	*prev;

// 	current = garb_col->head;
// 	while (current)
// 	{
// 		if (current->ptr_data == ptr)
// 		{
// 			free(current->ptr_data);
// 			if (prev == NULL)
// 				garb_col->head = current->next;
// 			else
// 				prev->next = current->next;
// 			free(current);
// 			return ;
// 		}
// 		prev = current;
// 		current = current->next;
// 	}
// }
