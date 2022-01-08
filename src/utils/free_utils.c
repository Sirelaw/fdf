/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 00:56:49 by oipadeol          #+#    #+#             */
/*   Updated: 2022/01/06 21:58:22 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

static void	free_row_nodes(t_node *node, void(*f)(void *))
{
	t_node	*next_p;

	if (node->next)
	{
		next_p = node->next;
		free_row_nodes(next_p, f);
	}
	f(node);
	node = NULL;
}

void	free_all(t_vars *vars)
{
	t_list	*input;
	t_list	*next_input;
	t_node	*node;

	input = vars->input;
	while (input)
	{
		next_input = input->next;
		node = input->content;
		free_row_nodes(node, free);
		free(input);
		input = next_input;
	}
	free(vars);
}
