/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 15:41:32 by oipadeol          #+#    #+#             */
/*   Updated: 2022/01/06 21:58:57 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

void	x_roll_all(t_list *input, double teta)
{
	t_node	*node;

	while (input)
	{
		node = input->content;
		while (node)
		{
			x_roll(node, teta);
			node = node->next;
		}
		input = input->next;
	}
}

void	y_roll_all(t_list *input, double teta)
{
	t_node	*node;

	while (input)
	{
		node = input->content;
		while (node)
		{
			y_roll(node, teta);
			node = node->next;
		}
		input = input->next;
	}
}

void	z_roll_all(t_list *input, double teta)
{
	t_node	*node;

	while (input)
	{
		node = input->content;
		while (node)
		{
			z_roll(node, teta);
			node = node->next;
		}
		input = input->next;
	}
}

void	rotate_image(int keycode, t_vars *vars)
{
	if (keycode == 0)
		y_roll_all(vars->input, -1 * M_PI_2 / 10);
	else if (keycode == 2)
		y_roll_all(vars->input, 1 * M_PI_2 / 10);
	else if (keycode == 13)
		x_roll_all(vars->input, 1 * M_PI_2 / 10);
	else if (keycode == 1)
		x_roll_all(vars->input, -1 * M_PI_2 / 10);
	else if (keycode == 12)
		z_roll_all(vars->input, -1 * M_PI_2 / 10);
	else if (keycode == 14)
		z_roll_all(vars->input, 1 * M_PI_2 / 10);
}
