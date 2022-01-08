/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plotline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:39:00 by oipadeol          #+#    #+#             */
/*   Updated: 2022/01/06 21:58:46 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

static void	init_v(int *dxy, int *xyi, int *count)
{
	*count = 0;
	if (*dxy < 0)
	{	
		*xyi = -1;
		*dxy = -1 * (*dxy);
	}
}

static void	plotLineLow(int x0_y0[2], int x1_y1[2], t_node *node, t_vars *vars)
{
	int	dx;
	int	dy;
	int	yi;
	int	D;
	int	count;

	dx = x1_y1[0] - x0_y0[0];
	dy = x1_y1[1] - x0_y0[1];
	yi = 1;
	D = (2 * dy) - dx;
	init_v(&dy, &yi, &count);
	while (x0_y0[0] <= x1_y1[0])
	{
		my_mlx_pixel_put(vars, x0_y0[0], x0_y0[1], node->color
			+ (vars->color_gradient * count++));
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

static void	plotLineHigh(int x0_y0[2], int x1_y1[2], t_node *node, t_vars *vars)
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
	init_v(&dx, &xi, &count);
	while (x0_y0[1] <= x1_y1[1])
	{
		my_mlx_pixel_put(vars, x0_y0[0], x0_y0[1], node->color
			+ (vars->color_gradient * count++));
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

static void	plotLine_elsepart(t_node *p_node, t_node *n_node, t_vars *vars)
{
	int	x0_y0[2];
	int	x1_y1[2];

	x0_y0[0] = (p_node->point[0] * vars->s_factor) + vars->oo[0] + vars->off[0];
	x0_y0[1] = (p_node->point[1] * vars->s_factor) + vars->oo[1] + vars->off[1];
	x1_y1[0] = (n_node->point[0] * vars->s_factor) + vars->oo[0] + vars->off[0];
	x1_y1[1] = (n_node->point[1] * vars->s_factor) + vars->oo[1] + vars->off[1];
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

void	plotLine(t_node *p_node, t_node *n_node, t_vars *vars)
{
	int	x0_y0[2];
	int	x1_y1[2];

	x0_y0[0] = (p_node->point[0] * vars->s_factor) + vars->oo[0] + vars->off[0];
	x0_y0[1] = (p_node->point[1] * vars->s_factor) + vars->oo[1] + vars->off[1];
	x1_y1[0] = (n_node->point[0] * vars->s_factor) + vars->oo[0] + vars->off[0];
	x1_y1[1] = (n_node->point[1] * vars->s_factor) + vars->oo[1] + vars->off[1];
	if (ft_absolute(x1_y1[1] - x0_y0[1]) < ft_absolute(x1_y1[0] - x0_y0[0]))
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
	plotLine_elsepart(p_node, n_node, vars);
}
