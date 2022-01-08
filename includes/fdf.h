/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 06:26:18 by oipadeol          #+#    #+#             */
/*   Updated: 2022/01/08 11:52:54 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include "get_next_line.h"

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_lenght;
	int		endian;
	float	s_factor;
	int		off[2];
	int		oo[2];
	int		color_gradient;
	int		map_w;
	int		map_l;
	t_list	*input;
}t_vars;

typedef struct s_node
{
	int		point[3];
	double	d_point[3];
	long	color;
	void	*next;
}t_node;

t_list	*input_rows(int argc, char **argv);
int		check_equal_size(t_list *input);

void	project_all(t_list	*input);
void	project_back(t_list *input);
void	x_roll(t_node *node, double teta);
void	y_roll(t_node *node, double teta);
void	z_roll(t_node *node, double teta);
void	x_roll_all(t_list *input, double teta);
void	y_roll_all(t_list *input, double teta);
void	z_roll_all(t_list *input, double teta);
void	rotate_image(int keycode, t_vars *vars);
void	move_image(int keycode, t_vars *vars);
void	zoom_image(int mousecode, int x, int y, t_vars *vars);
void	get_map_size(t_vars *vars);
void	node_lstadd_back(t_node **first, t_node *new_node);
int		node_lstsize(t_node *node);
t_node	*create_new_node(char *str, int row_n, int i);
t_node	*str_to_row(char *map_string, int row_n);
int		render_next_frame(t_vars *vars);
void	set_colorgradient(t_node *p_nod, t_node *n_node, t_vars *vars, char c);
void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color);
int		key_hook(int keycode, t_vars *vars);
int		mouse_hook(int mousecode, int x, int y, t_vars *vars);
int		clean_destroy(t_vars *vars);
void	check_map_color(t_vars *vars);
void	plotLine(t_node *p_node, t_node *n_node, t_vars *vars);
void	center_to_origin(t_list *input);
void	center_z_axis(t_vars *vars);
void	free_all(t_vars *vars);
t_node	*matrix_node_elem(t_list	*input, int x, int y);
t_node	*node_n_elem(t_node *node, int n);
void	print_all(t_list *input);
#endif