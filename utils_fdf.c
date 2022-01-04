/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fdf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 10:06:14 by oipadeol          #+#    #+#             */
/*   Updated: 2022/01/04 12:31:45 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_node *create_new_node(char *str, int row_n, int col_n)
{
	t_node	*new_node;
	char	**temp;

	new_node = malloc(sizeof(t_node));
	if (new_node == NULL)
		return (NULL);
	temp = ft_split(str, ',');
	if (temp == NULL)
		return (NULL);
	(new_node->point)[0] = col_n;
	(new_node->point)[1] = row_n;
	(new_node->point)[2] = ft_atoi(temp[0]);
	if (temp[1])
		new_node->color = ft_strtol(temp[1], NULL, 16);
	if (temp[1])
		free(temp[1]);
	else
		new_node->color = 0x00FFFFFF;
	new_node->next = NULL;
	free(temp[0]);
	free(temp);
	return(new_node);
}

void	node_lstadd_back(t_node **first, t_node *new_node)
{
	t_node	*p;

	p = *first;
	if (*first == NULL)
		*first = new_node;
	else
	{
		while (p->next != NULL)
			p = p->next;
		p->next = new_node;
	}
}

t_node	*node_n_elem(t_node *node, int n)
{
	t_node	*p;
	int		i;

	i = 0;
	p = node;
	while ((p != NULL) && (i < n))
	{
		p = p->next;
		i++;
	}
	if (i == n)
		return (p);
	else
		return (NULL);
}

int	node_lstsize(t_node *node)
{
	t_node	*p;
	int		i;

	p = node;
	i = 0;
	while (p != NULL)
	{
		p = p->next;
		i++;
	}
	return (i);
}

t_node	*matrix_node_elem(t_list	*input, int x, int y)
{
	int		m_elem;
	t_node	*elem;
	t_list	*p;

	elem = NULL;
	p = ft_lstelem(input, x);
	if (p != NULL)
		elem = (t_node *)(p->content);
	if (elem != NULL)
		elem = node_n_elem(elem, y);
	return (elem);
}

void	print_all(t_list *input)
{
	t_list	*temp;
	t_node	*node;

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
}

void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	dst = vars->addr + (y * vars->line_lenght + x * (vars->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	absolute(int n)
{
	if ((n < 0) && (n != INT_MIN))
		return (-1 * n);
	else
		return (n);
}

void	set_colorgradient(t_node *p_node, t_node *n_node, t_vars *vars, char c)
{
	int		dist;
	long	color_difference;
	int		increment;
	if (c == 'x')
		dist = (p_node->point[0] - n_node->point[0]) * vars->s_factor;
	else
		dist = (p_node->point[1] - n_node->point[1]) * vars->s_factor;
	color_difference = n_node->color - p_node->color;
	if (dist != 0)
		increment = color_difference / absolute(dist);
	else
		increment = 0;
	vars->color_gradient = increment;
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

void	plotLine(t_node *p_node, t_node *n_node, t_vars *vars)
{
	int x0_y0[2];
	int	x1_y1[2];

	x0_y0[0] = (p_node->proj[0] * vars->s_factor) + vars->origin[0];
	x0_y0[1] = (p_node->proj[1] * vars->s_factor) + vars->origin[1];
	x1_y1[0] = (n_node->proj[0] * vars->s_factor) + vars->origin[0];
	x1_y1[1] = (n_node->proj[1] * vars->s_factor) + vars->origin[1];
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

void	project_all(t_list *input)
{
	t_list	*temp;
	t_node	*node;

	while (input)
	{
		node = input->content;
		while (node)
		{
			node->proj[0] = node->point[0];
			node->proj[1] = node->point[1];
			node->proj[2] = node->point[2];
			node = node->next;
		}
		input = input->next;
	}
}