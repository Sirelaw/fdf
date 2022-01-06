/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 15:11:09 by oipadeol          #+#    #+#             */
/*   Updated: 2022/01/06 01:44:20 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	print_all(t_list *input)
{
	t_node	*node;

	while (input)
	{
		node = input->content;
		while (node)
		{
			printf("(%d, %d, %d) %ld", (node->point)[0], (node->point)[1],
				(node->point)[2], node->color);
			node = node->next;
		}
		printf("\n");
		input = input->next;
	}
}

t_node	*node_n_elem(t_node *node, int n)
{
	t_node	*p;
	int		i;

	i = 0;
	p = node;
	while ((p != NULL) && (i < n))
	{
		p = p->next;
		i++;
	}
	if (i == n)
		return (p);
	else
		return (NULL);
}

t_node	*matrix_node_elem(t_list *input, int x, int y)
{
	t_node	*elem;
	t_list	*p;

	elem = NULL;
	p = ft_lstelem(input, x);
	if (p != NULL)
		elem = (t_node *)(p->content);
	if (elem != NULL)
		elem = node_n_elem(elem, y);
	return (elem);
}
