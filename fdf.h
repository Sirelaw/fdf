/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 06:26:18 by oipadeol          #+#    #+#             */
/*   Updated: 2021/12/30 16:08:39 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include <math.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include "mlx/mlx.h"
#include "libft/libft.h"
#include "get_next_line/get_next_line.h"

typedef struct	s_data{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_lenght;
	int		endian;
}t_data;

typedef struct s_int
{
	int		size;
	int		*arr;
}t_int;

typedef struct	s_vars
{
	void	*mlx;
	void	*win;
}t_vars;

typedef struct	s_node
{
	int		point[3];
	int		proj[2];
	long	color;
	int		next;
}t_node;

t_list	*input_lines(int argc, char **argv);
t_int	*ft_new_t_int(int size, int *arr);
t_int	*str_to_int(char *map_string);
int		check_equal_size(t_list *input);
int		matrix_elem(t_list	*input, int x, int y);

void	translate(int state[3], int t_factor[3]);
void	scale(int state[3], int s_factor[3]);
void	x_roll(int state[3], float *teta);
void	y_roll(int state[3], float *teta);
void	z_roll(int state[3], float *teta);
void	project(t_node point, int camera[3], int dist, t_data *img);

void	tester(void);
#endif