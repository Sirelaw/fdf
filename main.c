/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 06:28:07 by oipadeol          #+#    #+#             */
/*   Updated: 2022/01/02 00:46:47 by oipadeol         ###   ########.fr       */
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

int	absolute(int n)
{
	if ((n < 0) && (n != INT_MIN))
		return (-1 * n);
	else
		return (n);
}

void	move_image(int keycode, t_vars *vars)
{
	int	n = 5;
	
	if (keycode == 123)
		vars->x_off -= n;
	else if (keycode == 124)
		vars->x_off += n;
	else if (keycode == 125)
		vars->y_off += n;
	else if (keycode == 126)
		vars->y_off -= n;
}

void	zoom_image(int mousecode, t_vars *vars)
{
	int	n = 50;
	
	if (mousecode == 4)
		vars->mesh_dist -= n;
	else if (mousecode == 5)
		if ((vars->mesh_dist + 5) < 1080)
			vars->mesh_dist += n;
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(EXIT_SUCCESS);	
	}
	if ((keycode >= 123) && (keycode <=126))
		move_image(keycode, vars);
	else
		printf("Hello from key_code: %d\n", keycode);
	return (0);
}

int	clean_destroy(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(EXIT_SUCCESS);	
}

int	mouse_hook(int mousecode, int x, int y, t_vars *vars)
{
	if ((mousecode == 4) && (mousecode == 5))
		zoom_image(mousecode, vars);
	printf("Hello from mouse_code: %d	%d	%d\n", mousecode, x, y);
	return (0);
}

void	my_mlx_pixel_put(t_vars *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_lenght + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void plotLineLow(int x0_y0[2], int x1_y1[2], t_node *node, t_vars *vars)
{
	int	dx;
	int	dy;
	int	yi;
	int	D;
	int count;

	dx = x1_y1[0] - x0_y0[0];
	dy = x1_y1[1] - x0_y0[1];
	yi = 1;
	D = (2 * dy) - dx;
	count = 0;
	if (dy < 0)
	{	
	    yi = -1;
	    dy = -dy;	
	}
	while (x0_y0[0] <= x1_y1[0])
	{
		my_mlx_pixel_put(vars, x0_y0[0], x0_y0[1], node->color + (vars->color_gradient * count++));
		if (D > 0)
		{
	        x0_y0[1] = x0_y0[1] + yi;
	        D = D + (2 * (dy - dx));		
		}
		else
	        D = D + (2 * dy);
		(x0_y0[0])++;
	}
}


void plotLineHigh(int x0_y0[2], int x1_y1[2], t_node *node, t_vars *vars)
{
	int	dx;
	int	dy;
	int	xi;
	int	D;
	int	count;

	dx = x1_y1[0] - x0_y0[0];
	dy = x1_y1[1] - x0_y0[1];
	xi = 1;
	D = (2 * dx) - dy;
	count = 0;
	if (dx < 0)
	{
	    xi = -1;
	    dx = -dx;
	}
	while (x0_y0[1] <= x1_y1[1])
	{
		my_mlx_pixel_put(vars, x0_y0[0], x0_y0[1], node->color + (vars->color_gradient * count++));
		if (D > 0)
		{
	        x0_y0[0] = x0_y0[0] + xi;
	        D = D + (2 * (dx - dy));		
		}
		else
	        D = D + (2 * dx);
		(x0_y0[1])++;
	}
}

void	set_colorgradient(t_node *p_node, t_node *n_node, t_vars *vars, char c)
{
	int		dist;
	long	color_difference;
	int		increment;

	if (c == 'x')
		dist = (p_node->proj[0] - n_node->proj[0]) * vars->mesh_dist;
	else
		dist = (p_node->proj[1] - n_node->proj[1]) * vars->mesh_dist;
	color_difference = n_node->color - p_node->color;
	increment = color_difference / absolute(dist);
	vars->color_gradient = increment;
}

void	plotLine(t_node *p_node, t_node *n_node, t_vars *vars)
{
	int x0_y0[2];
	int	x1_y1[2];

	x0_y0[0] = p_node->proj[0] * vars->mesh_dist;
	x0_y0[1] = p_node->proj[1] * vars->mesh_dist;
	x1_y1[0] = n_node->proj[0] * vars->mesh_dist;
	x1_y1[1] = n_node->proj[1] * vars->mesh_dist;
	if (absolute(x1_y1[1] - x0_y0[1]) < absolute(x1_y1[0] - x0_y0[0]))
	{
		if (x0_y0[0] > x1_y1[0])
			set_colorgradient(n_node, p_node, vars, 'x');
		if (x0_y0[0] > x1_y1[0])
			plotLineLow(x1_y1, x0_y0, n_node, vars);
		else
		{
			set_colorgradient(p_node, n_node, vars, 'x');
			plotLineLow(x0_y0, x1_y1, p_node, vars);
		}
		return ;
	}
	if (x0_y0[1] > x1_y1[1])
		set_colorgradient(n_node, p_node, vars, 'y');
	if (x0_y0[1] > x1_y1[1])
		plotLineHigh(x1_y1, x0_y0, n_node, vars);
	else
	{
		set_colorgradient(p_node, n_node, vars, 'y');
		plotLineHigh(x0_y0, x1_y1, p_node, vars);
	}
}

void	draw_wire_frame(t_vars *vars, t_list *input)
{
	int i;
	int j;
	t_node	*present_node;
	t_node	*down_node;

	i = node_lstsize(((t_node *)(input->content)));
	j = ft_lstsize(input);
	vars->mesh_dist = 500 / bigger(i, j);
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

void	print_all(t_list *input)
{
	t_list	*temp;
	t_node	*node;

	temp = input;
	while (input)
	{
		node = input->content;
		while (node)
		{
			printf("(%d, %d, %d) %ld	", (node->point)[0], (node->point)[1], (node->point)[2], node->color);
			node = node->next;
		}
		printf("\n");
		input = input->next;
	}
	while (temp)
	{
		node = temp->content;
		while (node)
		{
			printf("(%d, %d) %ld	", (node->proj)[0], (node->proj)[1], node->color);
			node = node->next;
		}
		printf("\n");
		temp = temp->next;
	}
}

int	render_next_frame(t_vars *vars)
{
	mlx_clear_window(vars->mlx, vars->win);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, vars->x_off, vars->y_off);
	return (0);
}

void	initialize_angles_offset(t_vars *vars)
{
	vars->x_off=0;
	vars->y_off=0;
	vars->x_ang=0;
	vars->y_ang=0;
	vars->z_ang=0;
	(vars->camera_loc)[0] = 0;
	(vars->camera_loc)[1] = 0;
	(vars->camera_loc)[2] = 0;
	vars->camera_dist = 1;
}

int	main(int argc, char **argv)
{
	t_vars	*vars;

	errno = 0;
	vars = malloc(sizeof(t_vars));
	vars->input = input_rows(argc, argv);
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, 1800, 1080, "Hello world!");
	vars->img = mlx_new_image(vars->mlx, 1800, 1080);
	vars->addr = mlx_get_data_addr(vars->img, &vars->bits_per_pixel, &vars->line_lenght,
		&vars->endian);
	initialize_angles_offset(vars);
	project_all(vars, vars->camera_loc, vars->camera_dist);
	// print_all(vars->input);
	// draw_wire_frame(vars, vars->input);
	draw_wire_frame(vars, vars->input);
	mlx_hook(vars->win, 2, 1L<<0, key_hook, vars);
	mlx_mouse_hook (vars->win, mouse_hook, vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, vars->x_off, vars->y_off);
	mlx_loop_hook(vars->mlx, render_next_frame, vars);
	mlx_loop(vars->mlx);
	return (0);
}
