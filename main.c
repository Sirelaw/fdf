/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 06:28:07 by oipadeol          #+#    #+#             */
/*   Updated: 2022/01/06 05:19:05 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_wire_frame(t_vars *vars, t_list *input)
{
	t_node	*present_node;
	t_node	*down_node;

	while (input)
	{
		present_node = input->content;
		if (input->next)
			down_node = (input->next)->content;
		while (present_node)
		{
			if (present_node->next)
				plotLine(present_node, present_node->next, vars);
			if (input->next)
			{
				plotLine(present_node, down_node, vars);
				down_node = down_node->next;
			}
			present_node = present_node->next;
		}
		input = input->next;
	}
}

int	render_next_frame(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img);
	vars->img = mlx_new_image(vars->mlx, vars->map_w, vars->map_l);
	vars->addr = mlx_get_data_addr(vars->img, &vars->bits_per_pixel,
			&vars->line_lenght, &vars->endian);
	draw_wire_frame(vars, vars->input);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	return (0);
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
	if (vars->map_w < 400)
		vars->map_w = 400;
	if (vars->map_l < 400)
		vars->map_l = 400;
	if (vars->map_l > 1300)
		vars->map_l = 1300;
	vars->oo[0] = vars->map_w / 2;
	vars->oo[1] = vars->map_l / 2;
}

void	initialize_angles_offset(t_vars *vars)
{
	center_to_origin(vars->input);
	check_map_color(vars);
	get_map_size(vars);
	vars->off[0] = 0;
	vars->off[1] = 0;
	project_all(vars->input);
	x_roll_all(vars->input, (M_PI_2 / 2));
	y_roll_all(vars->input, -1 * (M_PI_2 / 2));
	z_roll_all(vars->input, (M_PI_2 / 3));
}

int	main(int argc, char **argv)
{
	t_vars	*vars;

	vars = malloc(sizeof(t_vars));
	vars->input = input_rows(argc, argv);
	initialize_angles_offset(vars);
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, vars->map_w,
			vars->map_l, "ELAW_FDF");
	vars->img = mlx_new_image(vars->mlx, vars->map_w, vars->map_l);
	vars->addr = mlx_get_data_addr(vars->img, &vars->bits_per_pixel,
			&vars->line_lenght, &vars->endian);
	draw_wire_frame(vars, vars->input);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	mlx_hook(vars->win, 2, 1L << 0, key_hook, vars);
	mlx_mouse_hook (vars->win, mouse_hook, vars);
	mlx_hook(vars->win, 17, 0, clean_destroy, vars);
	mlx_loop(vars->mlx);
	return (0);
}
