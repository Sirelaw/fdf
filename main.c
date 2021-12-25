/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 06:28:07 by oipadeol          #+#    #+#             */
/*   Updated: 2021/12/23 16:18:36 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

typedef struct	s_data{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_lenght;
	int		endian;
}t_data;

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

void	draw_inner_square(t_data *img)
{
	int i;
	int	j;

	i = 600;
	while (i < 900)
	{
		j = 350;
		while (j < 651)
		{
			if ((i == 600) || (i == 899))
				my_mlx_pixel_put(img, i, j, 0x0000FFFF);
			if ((j == 350) || (j == 650))
				my_mlx_pixel_put(img, i, j, 0x0000FFFF);
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	int		i;
	t_vars	vars;
	t_data	img;
	t_list	*input;

	errno = 0;
	i = 4;
	input = input_lines(argc, argv);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1800, 1080, "Hello world!");
	img.img = mlx_new_image(vars.mlx, 1800, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_lenght, 
		&img.endian);
	draw_square(&img);
	draw_inner_square(&img);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_mouse_hook (vars.win, mouse_hook, &vars);
	mlx_hook(vars.win, 2, 1L<<0, key_hook, &vars);
	// draw_wire_frame(&img, input)
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_loop(vars.mlx);
	return (0);
}