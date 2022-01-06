/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_matrix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:14:53 by oipadeol          #+#    #+#             */
/*   Updated: 2022/01/05 00:44:47 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	z_roll(t_node *node, double teta)
{
	double	temp_x;
	double	temp_y;

	temp_x = node->d_point[0];
	temp_y = node->d_point[1];
	node->d_point[0] = (temp_x * cos(teta)) - (temp_y * sin(teta));
	node->d_point[1] = (temp_x * sin(teta)) + (temp_y * cos(teta));
	node->point[0] = node->d_point[0];
	node->point[1] = node->d_point[1];
}

void	x_roll(t_node *node, double teta)
{
	double	temp_y;
	double	temp_z;

	temp_y = node->d_point[1];
	temp_z = node->d_point[2];
	node->d_point[1] = (temp_y * cos(teta)) - (temp_z * sin(teta));
	node->d_point[2] = (temp_y * sin(teta)) + (temp_z * cos(teta));
	node->point[1] = node->d_point[1];
	node->point[2] = node->d_point[2];
}

void	y_roll(t_node *node, double teta)
{
	double	temp_z;
	double	temp_x;

	temp_z = node->d_point[2];
	temp_x = node->d_point[0];
	node->d_point[2] = (temp_z * cos(teta)) - (temp_x * sin(teta));
	node->d_point[0] = (temp_z * sin(teta)) + (temp_x * cos(teta));
	node->point[2] = node->d_point[2];
	node->point[0] = node->d_point[0];
}
