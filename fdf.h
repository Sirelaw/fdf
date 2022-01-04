/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 06:26:18 by oipadeol          #+#    #+#             */
/*   Updated: 2022/01/04 13:25:51 by oipadeol         ###   ########.fr       */
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

typedef struct	s_vars
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_lenght;
	int		endian;
	float	s_factor;
	int		offset[2];
	int		origin[2];
	double	angle[3];
	int		rotate_flag[3];
	int		need_render;
	int		color_gradient;
	t_list	*input;
}t_vars;

typedef struct	s_node
{
	int		point[3];
	int		proj[3];
	long	color;
	void	*next;
}t_node;

t_list	*input_rows(int argc, char **argv);
int		check_equal_size(t_list *input);
long	ft_strtol(const char *str, char **end_ptr, int base);

void	translate(int state[3], int t_factor[3]);
void	project_all(t_list	*input);
void	x_roll(int state[3], double teta);
void	y_roll(int state[3], double teta);
void	z_roll(int state[3], double teta);
void	node_lstadd_back(t_node **first, t_node *new_node);
int		node_lstsize(t_node *node);
t_node	*create_new_node(char *str, int row_n, int i);
t_node	*str_to_row(char *map_string, int row_n);
t_node	*matrix_node_elem(t_list	*input, int x, int y);
t_node	*node_n_elem(t_node *node, int n);
void	print_all(t_list *input);
int		render_next_frame(t_vars *vars);
void	set_colorgradient(t_node *p_nod, t_node *n_node, t_vars *vars, char c);
void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color);
void	plotLine(t_node *p_node, t_node *n_node, t_vars *vars);
void	roll_test(t_list *input);
#endif