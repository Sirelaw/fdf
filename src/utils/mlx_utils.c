/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 15:15:33 by oipadeol          #+#    #+#             */
/*   Updated: 2022/01/08 11:44:06 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	if ((x >= vars->map_w) || (y >= vars->map_l) || (x < 0) || (y < 0))
		return ;
	dst = vars->addr + (y * vars->line_lenght + x * (vars->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 53)
		clean_destroy(vars);
	if (((keycode >= 0) && (keycode <= 2)) || ((keycode >= 12)
			&& (keycode <= 14)))
		rotate_image(keycode, vars);
	else if ((keycode >= 123) && (keycode <= 126))
		move_image(keycode, vars);
	render_next_frame(vars);
	return (0);
}

int	mouse_hook(int mousecode, int x, int y, t_vars *vars)
{
	if ((mousecode == 4) || (mousecode == 5))
	{
		zoom_image(mousecode, x, y, vars);
		render_next_frame(vars);
	}
	return (0);
}

int	clean_destroy(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	free_all(vars);
	exit(EXIT_SUCCESS);
}
