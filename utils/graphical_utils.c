/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphical_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 15:46:05 by oipadeol          #+#    #+#             */
/*   Updated: 2022/01/06 04:17:22 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	move_image(int keycode, t_vars *vars)
{
	int	n;

	n = 4;
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
