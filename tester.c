/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:41:51 by oipadeol          #+#    #+#             */
/*   Updated: 2021/12/30 13:04:09 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	tester(void)
{
	float	state[3];
	float	teta = -1 * M_PI_4;
	int t_factor[3];
	int	i = 0;

	state[0] = 4;
	state[1] = 3;
	state[2] = 0;
	// t_factor[0] = 2;
	// t_factor[1] = 3;
	// t_factor[2] = 4;
	y_roll(state, &teta);
	while (i++ < 3)
		printf("%f\n", state[i - 1]);
		// printf("%f\n", sin(*(&teta)));

	// float n = 1.5708;
	// float	o = n;
	// double	t = n;

	// printf("float(%f): %f	double(%f): %f\n", o, cosf(o), t, cos(t));
}