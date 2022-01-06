/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:43:26 by oipadeol          #+#    #+#             */
/*   Updated: 2022/01/06 05:10:28 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	set_colorgradient(t_node *p_node, t_node *n_node, t_vars *vars, char c)
{
	int		dist;
	long	color_difference;
	int		increment;

	if (c == 'x')
		dist = (p_node->point[0] - n_node->point[0]) * vars->s_factor;
	else
		dist = (p_node->point[1] - n_node->point[1]) * vars->s_factor;
	color_difference = n_node->color - p_node->color;
	if (dist != 0)
		increment = color_difference / ft_absolute(dist);
	else
		increment = 0;
	vars->color_gradient = increment;
}

void	project_all(t_list *input)
{
	t_node	*node;

	while (input)
	{
		node = input->content;
		while (node)
		{
			node->d_point[0] = node->point[0];
			node->d_point[1] = node->point[1];
			node->d_point[2] = node->point[2];
			node = node->next;
		}
		input = input->next;
	}
}

static void	reset_all_z(t_vars *vars, int difference)
{
	t_node	*node;
	t_list	*input;

	input = vars->input;
	while (input)
	{
		node = input->content;
		while (node)
		{
			node->point[2] = node->point[2] - (difference / 2);
			node = node->next;
		}
		input = input->next;
	}
}

void	center_z_axis(t_vars *vars)
{
	int		max;
	int		min;
	t_list	*input;
	t_node	*node;

	max = 0;
	min = 0;
	input = vars->input;
	while (input)
	{
		node = input->content;
		while (node)
		{
			if ((node->point)[2] > max)
				max = (node->point[2]);
			if ((node->point)[2] < min)
				min = (node->point[2]);
			node = node->next;
		}
		input = input->next;
	}
	reset_all_z(vars, max - min);
}

void	center_to_origin(t_list *input)
{
	int		i;
	int		j;
	int		temp;
	t_node	*node;

	node = input->content;
	i = -1 * (node_lstsize(node) / 2);
	j = -1 * (ft_lstsize(input) / 2);
	temp = i;
	while (input)
	{
		node = input->content;
		i = temp;
		while (node)
		{
			(node->point)[0] = i * 20;
			(node->point)[1] = j * 20;
			(node->point)[2] = (node->point)[2] * 20;
			node = node->next;
			i++;
		}
		input = input->next;
		j++;
	}
}
