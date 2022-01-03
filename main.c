/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 06:28:07 by oipadeol          #+#    #+#             */
/*   Updated: 2022/01/03 23:57:14 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	bigger(int n1, int n2)
{
	if (n1 > n2)
		return (n1);
	else
		return (n2);
}

void	x_roll_all(t_list *input, double teta)
{
	t_node	*node;

	while (input)
	{
		node = input->content;
		while (node)
		{
			x_roll(node->point, teta);
			node = node->next;
		}
		input = input->next;
	}
}

void	y_roll_all(t_list *input, double teta)
{
	t_node	*node;

	while (input)
	{
		node = input->content;
		while (node)
		{
			y_roll(node->point, teta);
			node = node->next;
		}
		input = input->next;
	}
}

void	z_roll_all(t_list *input, double teta)
{
	t_node	*node;

	while (input)
	{
		node = input->content;
		while (node)
		{
			z_roll(node->point, teta);
			node = node->next;
		}
		input = input->next;
	}
}

void	rotate_image(int keycode, t_vars *vars)
{
	double	n;
	
	n = 0.1;
	if (keycode == 0)
		y_roll_all(vars->input, -0.1);
	else if (keycode == 2)
		y_roll_all(vars->input, 0.1);
	else if (keycode == 13)
		x_roll_all(vars->input, 0.1);
	else if (keycode == 1)
		x_roll_all(vars->input, -0.1);
	else if (keycode == 12)
		z_roll_all(vars->input, -0.1);
	else if (keycode == 14)
		z_roll_all(vars->input, 0.1);
}

void	move_image(int keycode, t_vars *vars)
{
	int	n = 4;
	
	if (keycode == 123)
		vars->offset[0] -= n;
	else if (keycode == 124)
		vars->offset[0] += n;
	else if (keycode == 125)
		vars->offset[1] += n;
	else if (keycode == 126)
		vars->offset[1] -= n;
	vars->need_render = 0;
}

void	zoom_image(int mousecode, t_vars *vars)
{
	float	n = 1.1;
	
	if (mousecode == 4)
		vars->mesh_dist = vars->mesh_dist / n;
	else if (mousecode == 5)
		if ((vars->mesh_dist + 5) < 1080)
			vars->mesh_dist *= n;
	if (vars->mesh_dist < 1)
		vars->mesh_dist = 1;
	vars->need_render = 1;
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(EXIT_SUCCESS);	
	}
	if (((keycode >= 0) && (keycode <= 2)) || ((keycode >= 12) && (keycode <= 14)))
			rotate_image(keycode, vars);
	else if ((keycode >= 123) && (keycode <=126))
		move_image(keycode, vars);
	else
		printf("Hello from key_code: %d\n", keycode);
	render_next_frame(vars);
	return (0);
}

int	clean_destroy(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(EXIT_SUCCESS);	
}

int	mouse_hook(int mousecode, int x, int y, t_vars *vars)
{
	if ((mousecode == 4) || (mousecode == 5))
	{
		render_next_frame(vars);
		zoom_image(mousecode, vars);
	}
	else
		printf("Hello from mouse_code: %d	%d	%d\n", mousecode, x, y);
	return (0);
}

void	draw_wire_frame(t_vars *vars, t_list *input)
{
	int i;
	int j;
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
	if (!(vars->need_render))
		mlx_clear_window(vars->mlx, vars->win);
	else
	{
		mlx_destroy_image(vars->mlx, vars->img);
		vars->img = mlx_new_image(vars->mlx, 1800, 1080);
		vars->addr = mlx_get_data_addr(vars->img, &vars->bits_per_pixel, &vars->line_lenght,
			&vars->endian);
		draw_wire_frame(vars, vars->input);
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, vars->offset[0], vars->offset[1]);
	return (0);
}

void	center_to_origin(t_list *input)
{
	int i;
	int j;
	int	temp;
	t_node	*node;

	node = input->content;
	i = node_lstsize(node);
	j = ft_lstsize(input);
	i = -1 * (i / 2);
	j = -1 * (j / 2);
	temp = i;
	while (input)
	{
		node = input->content;
		i = temp;
		while (node)
		{
			(node->point)[0] = i;
			(node->point)[1] = j;
			node = node->next;
			i++;
		}
		input = input->next;
		j++;
	}
}

void	initialize_angles_offset(t_vars *vars)
{
	center_to_origin(vars->input);
	vars->offset[0] = 0;
	vars->offset[1] = 0;
	vars->origin[0] = 500;
	vars->origin[1] = 500;
	vars->mesh_dist = 1;
	vars->need_render = 1;
}

int	main(int argc, char **argv)
{
	t_vars	*vars;
	int i = 10;
	
	errno = 0;
	vars = malloc(sizeof(t_vars));
	vars->input = input_rows(argc, argv);
	initialize_angles_offset(vars);
	// while (i--)
	// roll_test(vars->input);
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, 1800, 1080, "FT_FDF");
	vars->img = mlx_new_image(vars->mlx, 1800, 1080);
	vars->addr = mlx_get_data_addr(vars->img, &vars->bits_per_pixel, &vars->line_lenght,
		&vars->endian);
	draw_wire_frame(vars, vars->input);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	mlx_hook(vars->win, 2, 1L<<0, key_hook, vars);
	mlx_mouse_hook (vars->win, mouse_hook, vars);
	mlx_loop(vars->mlx);
	return (0);
}
