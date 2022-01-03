/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:14:53 by oipadeol          #+#    #+#             */
/*   Updated: 2022/01/03 23:52:17 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	translate(int state[3], int t_factor[3])
{
	state[0] = state[0] + t_factor[0];
	state[1] = state[1] + t_factor[1];
	state[2] = state[2] + t_factor[2];
}

void	scale(int state[3], int s_factor[3])
{
	state[0] = state[0] * s_factor[0];
	state[1] = state[1] * s_factor[1];
	state[2] = state[2] * s_factor[2];
}

void	z_roll(int positon[3], float teta)
{
	int	temp;

	temp = positon[0];
	positon[0] = (temp * cos(teta)) - (positon[1] * sin(teta));
	positon[1] = (temp * sin(teta)) + (positon[1] * cos(teta));
}

void	x_roll(int positon[3], double teta)
{
	double	temp_y;
	double	temp_z;

	temp_y = positon[1];
	temp_z = positon[2];
	positon[1] = (temp_y * cos(teta)) - (temp_z * sin(teta));
	positon[2] = (temp_y * sin(teta)) + (temp_z * cos(teta));
}

void	y_roll(int positon[3], float teta)
{
	int	temp;

	temp = positon[2];
	positon[2] = (temp * cos(teta)) - (positon[0] * sin(teta));
	positon[0] = (temp * sin(teta)) + (positon[0] * cos(teta));
}
