/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 19:37:12 by oipadeol          #+#    #+#             */
/*   Updated: 2022/01/03 22:43:53 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	x_roller(int positon[3], double teta)
{
	double	temp_y;
	double	temp_z;

	temp_y = positon[1];
	temp_z = positon[2];
	printf("Before (x,y,z): (%d, %d, %d)\n", positon[0], positon[1], positon[2]);
	positon[1] = (temp_y * cos(teta)) - (temp_z * sin(teta));
	positon[2] = (temp_y * sin(teta)) + (temp_z * cos(teta));
	printf("After (x,y,z): (%d, %d, %d)\n", positon[0], positon[1], positon[2]);
	
}

void	z_roller(int positon[3], float teta)
{
	double	temp;

	temp = positon[0];
	printf("Before (x,y,z): (%d, %d, %d)\n", positon[0], positon[1], positon[2]);
	positon[0] = (temp * cos(teta)) - (positon[1] * sin(teta));
	positon[1] = (temp * sin(teta)) + (positon[1] * cos(teta));
	printf("After (x,y,z): (%d, %d, %d)\n", positon[0], positon[1], positon[2]);
}

void	roll_test(t_list *input)
{
	int	position[3];
	double	teta;
	t_list	*temp;
	t_node	*node;
	teta = -1 * 0.1;
	
	while (input)
	{
		node = input->content;
		while (node)
		{
			z_roller(node->point, teta);
			node = node->next;
		}
		input = input->next;
	}
}