/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3D_to_2D.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 13:04:48 by oipadeol          #+#    #+#             */
/*   Updated: 2022/01/01 19:29:02 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	project(t_node point, int camera[3], int dist, t_vars *vars)
{
	(point.proj)[0] = (((point.point)[0] - camera[0])
				 * (dist / (point.point)[2])) + camera[0];
	(point.proj)[1] = (((point.point)[1] - camera[1])
				 * (dist / (point.point)[2])) + camera[1];
}

void	project_all(t_vars *vars, int camera[3], int dist)
{
	t_list	*input;
	t_node	*point;
	
	input = vars->input;
	while (input)
	{
		point = input->content;
		while (point)
		{
			// (point->proj)[0] = (((point->point)[0] - camera[0])
			// 	 * (dist / (point->point)[2])) + camera[0];
			// (point->proj)[1] = (((point->point)[1] - camera[1])
			// 	 * (dist / (point->point)[2])) + camera[1];
			// point = point->next;

			(point->proj)[0] = (point->point)[0];
			(point->proj)[1] = (point->point)[1];
			point = point->next;
		}
	input = input->next;
	}
}
