/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3D_to_2D.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 13:04:48 by oipadeol          #+#    #+#             */
/*   Updated: 2021/12/30 13:40:35 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	project(t_node point, int camera[3], int dist, t_data *img)
{
	(point.proj)[0] = (((point.point)[0] - camera[0])
				 * (dist / (point.point)[2])) + camera[0];
	(point.proj)[1] = (((point.point)[1] - camera[1])
				 * (dist / (point.point)[2])) + camera[1];
}
