/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 06:28:07 by oipadeol          #+#    #+#             */
/*   Updated: 2021/12/30 13:21:51 by oipadeol         ###   ########.fr       */
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

void	put_pixel(int x, int y)
{
	
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(EXIT_SUCCESS);	
	}
	printf("Hello from key_code: %d\n", keycode);
	return (0);
}

int	mouse_hook(int mousecode, int x, int y, t_vars *vars)
{
	printf("Hello from mouse_code: %d	%d	%d\n", mousecode, x, y);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_lenght + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_square(t_data *img)
{
	int i;
	int	j;

	i = 500;
	while (i < 1000)
	{
		j = 250;
		while (j < 751)
		{
			if ((i == 500) || (i == 999))
				my_mlx_pixel_put(img, i, j, 0x0000FFFF);
			if ((j == 250) || (j == 750))
				my_mlx_pixel_put(img, i, j, 0x0000FFFF);
			j++;
		}
		i++;
	}
}



// void	draw_wire_frame(t_data *img, t_list *input)
// {
// 	int i;
// 	int j;
// 	int	x_dist;
// 	int	y_dist;
// 	int x_off = 100;
// 	int y_off = 100;
// 	int count;
// 	int point = x_off;

// 	int	x = 250;
// 	int	y = 250;

// 	i = ((t_int *)(input->content))->size;
// 	j = ft_lstsize(input);
// 	x_dist = x / bigger(i, j);
// 	y_dist = y / bigger(i, j);
// 	while (input)
// 	{
// 		count = 0;
// 		while (count < i)
// 		{
// 			point = point + x_dist;
// 			my_mlx_pixel_put(img, point, y_off - (((t_int *)(input->content))->arr)[count], 0x0000FFFF);
// 			count++;
// 		}
// 		point = x_off;
// 		y_off = y_off + y_dist;
// 		input = input->next;
// 	}
// }

void plotLineLow(int x, int y, int x1, int y1, t_data *img)
{
	int	dx;
	int	dy;
	int	yi;
	int	D;

	dx = x1 - x;
	dy = y1 - y;
	yi = 1;
	D = (2 * dy) - dx;
	if (dy < 0)
	{	
	    yi = -1;
	    dy = -dy;	
	}
	while (x <= x1)
	{
		my_mlx_pixel_put(img, x, y, 0x0000FFFF);
		if (D > 0)
		{
	        y = y + yi;
	        D = D + (2 * (dy - dx));		
		}
		else
	        D = D + (2 * dy);
		x++;
	}
}

void plotLineHigh(int x, int y, int x1, int y1, t_data *img)
{
	int	dx;
	int	dy;
	int	xi;
	int	D;
	
	dx = x1 - x;
	dy = y1 - y;
	xi = 1;
	D = (2 * dx) - dy;
	if (dx < 0)
	{	
	    xi = -1;
	    dx = -dx;	
	}
	while (y <= y1)
	{
		my_mlx_pixel_put(img, x, y, 0x0000FFFF);
		if (D > 0)
		{
	        x = x + xi;
	        D = D + (2 * (dx - dy));		
		}
		else
	        D = D + (2 * dx);
		y++;
	}
}

void	plotLine(int x0, int y0, int x1, int y1, t_data *img)
{
    if (absolute(y1 - y0) < absolute(x1 - x0))
	{
        if (x0 > x1)
            plotLineLow(x1, y1, x0, y0, img);
        else
            plotLineLow(x0, y0, x1, y1, img);
	}
    else
	{
        if (y0 > y1)
            plotLineHigh(x1, y1, x0, y0, img);
        else
            plotLineHigh(x0, y0, x1, y1, img);
	}
}

void	draw_wire_frame(t_data *img, t_list *input)
{
	int i;
	int j;
	int	x_dist;
	int	y_dist;
	int x_off = 200;
	int y_off = 200;
	int count;
	int point = x_off;

	int flag = 0;
	int	x = 900;
	int	y = 900;

	i = ((t_int *)(input->content))->size;
	j = ft_lstsize(input);
	x_dist = x / bigger(i, j);
	y_dist = y / bigger(i, j);
	while (input)
	{
		count = 0;
		while (count < i)
		{
			point = point + x_dist;
			// my_mlx_pixel_put(img, point, y_off - (((t_int *)(input->content))->arr)[count], 0x0000FFFF);
			// my_mlx_pixel_put(img, point, y_off, 0x0000FFFF);
			if (count != 0)
				plotLine(point - x_dist, y_off, point, y_off, img);
			if (flag != 0)
				plotLine(point, y_off - y_dist, point, y_off, img);
			count++;
		}
		point = x_off;
		y_off = y_off + y_dist;
		input = input->next;
		flag = 1;
	}
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_data	img;
	t_list	*input;

	errno = 0;
	input = input_lines(argc, argv);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1800, 1080, "Hello world!");
	img.img = mlx_new_image(vars.mlx, 1800, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_lenght, 
		&img.endian);
	tester();
	draw_wire_frame(&img, input);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_mouse_hook (vars.win, mouse_hook, &vars);
	mlx_hook(vars.win, 2, 1L<<0, key_hook, &vars);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_loop(vars.mlx);
	return (0);
}