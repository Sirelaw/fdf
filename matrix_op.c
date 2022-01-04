/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:14:53 by oipadeol          #+#    #+#             */
/*   Updated: 2022/01/04 13:26:08 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	z_roll(int project[3], double teta)
{
	int	temp;

	temp = project[0];
	project[0] = (temp * cos(teta)) - (project[1] * sin(teta));
	project[1] = (temp * sin(teta)) + (project[1] * cos(teta));
}

void	x_roll(int project[3], double teta)
{
	int	temp;

	temp = project[1];
	project[1] = (temp * cos(teta)) - (project[2] * sin(teta));
	project[2] = (temp * sin(teta)) + (project[2] * cos(teta));
}

void	y_roll(int project[3], double teta)
{
	int	temp;

	temp = project[2];
	project[2] = (temp * cos(teta)) - (project[0] * sin(teta));
	project[0] = (temp * sin(teta)) + (project[0] * cos(teta));
}
