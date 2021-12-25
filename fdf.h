/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 06:26:18 by oipadeol          #+#    #+#             */
/*   Updated: 2021/12/22 20:31:42 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <limits.h>
#include <fcntl.h>
#include "mlx/mlx.h"
#include "libft/libft.h"
#include "get_next_line/get_next_line.h"

typedef struct s_int
{
	int		size;
	int		*arr;
}t_int;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}t_vars;

t_list	*input_lines(int argc, char **argv);
t_int	*ft_new_t_int(int size, int *arr);
t_int	*str_to_int(char *map_string);
int		check_equal_size(t_list *input);
int		matrix_elem(t_list	*input, int x, int y);
#endif