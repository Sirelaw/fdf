/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 06:28:07 by oipadeol          #+#    #+#             */
/*   Updated: 2021/12/19 12:09:57 by oipadeol         ###   ########.fr       */
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

	i = 20;
	while (i < 421)
	{
		j = 20;
		while (j < 421)
		{
			if ((i == 20) || (i == 420))
				my_mlx_pixel_put(img, i , j, 0x0000FFFF);
			if ((j == 20) || (j == 420))
				my_mlx_pixel_put(img, i , j, 0x0000FFFF);
			j++;
		}
		i++;
	}
	// i = 5;
	// while (i++ < 795)
	// 	my_mlx_pixel_put(img, i , 400, 0x0000FFFF);
}

int	main(int argc, char **argv)
{
	void	*mlx;
	t_data	img;
	void	*mlx_win;
	int		i;
	t_list	*input;

	errno = 0;
	i = 4;
	input = input_lines(argc, argv);
	// mlx = mlx_init();
	// mlx_win = mlx_new_window(mlx, 800, 800, "Hello world!");
	// img.img = mlx_new_image(mlx, 800, 800);
	// img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_lenght, 
	// 	&img.endian);
	// draw_square(&img);
	// // while (i++ < 795)
	// // 	my_mlx_pixel_put(&img, i , 400, 0x0000FFFF);
	// mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	// mlx_loop(mlx);
	
}