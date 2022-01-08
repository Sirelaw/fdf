/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphical_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 15:46:05 by oipadeol          #+#    #+#             */
/*   Updated: 2022/01/07 15:26:34 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

void	move_image(int keycode, t_vars *vars)
{
	int	n;

	n = 10;
	if (keycode == 123)
		vars->off[0] -= n;
	else if (keycode == 124)
		vars->off[0] += n;
	else if (keycode == 125)
		vars->off[1] += n;
	else if (keycode == 126)
		vars->off[1] -= n;
}

void	zoom_image(int mousecode, int x, int y, t_vars *vars)
{
	float	n;

	n = 1.1;
	if (mousecode == 4)
	{
		vars->s_factor = vars->s_factor / n;
		vars->off[0] = vars->off[0] - (vars->off[0] / 10);
		vars->off[1] = vars->off[1] - (vars->off[1] / 10);
	}
	else if (mousecode == 5)
	{
		vars->s_factor *= n;
		vars->off[0] = vars->off[0] + (vars->oo[0] - x) / 5;
		vars->off[1] = vars->off[1] + (vars->oo[1] - y) / 5;
	}
}

void	get_map_size(t_vars *vars)
{
	int	i;
	int	j;

	i = node_lstsize((t_node *)(vars->input->content));
	j = ft_lstsize(vars->input);
	if (i <= 50)
		vars->map_w = j * 30;
	else
		vars->map_w = i * 5;
	if (j <= 50)
		vars->map_l = j * 30;
	else
		vars->map_l = j * 5;
	if (i > 100)
		vars->s_factor = 0.2;
	else
		vars->s_factor = 1;
	if (vars->map_w < 500)
		vars->map_w = 500;
	if (vars->map_l < 500)
		vars->map_l = 500;
	if (vars->map_l > 1300)
		vars->map_l = 1300;
	vars->oo[0] = vars->map_w / 2;
	vars->oo[1] = vars->map_l / 2;
}

static void	reset_all_color(t_vars *vars, int max, int min)
{
	t_node	*node;
	t_list	*input;
	double	difference;
	int		color_difference;

	input = vars->input;
	color_difference = 0x00FFFFFF - 0x0000FFFF;
	difference = max - min;
	while (input)
	{
		node = input->content;
		while (node)
		{
			node->color = (((max - node->point[2]) / difference)
					* color_difference) + 0x0000FFFF;
			node = node->next;
		}
		input = input->next;
	}
}

void	check_map_color(t_vars *vars)
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
			if ((node->color) != 0x00FFFFFF)
				return ;
			if ((node->point)[2] > max)
				max = (node->point[2]);
			if ((node->point)[2] < min)
				min = (node->point[2]);
			node = node->next;
		}
		input = input->next;
	}
	if (max - min)
		reset_all_color(vars, max, min);
}
