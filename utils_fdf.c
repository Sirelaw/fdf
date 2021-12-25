/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fdf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 10:06:14 by oipadeol          #+#    #+#             */
/*   Updated: 2021/12/21 13:18:15 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_int	*ft_new_t_int(int size, int *arr)
{
	t_int	*new_elem;

	new_elem = malloc(sizeof(t_int));
	if (new_elem == NULL)
		return (NULL);
	new_elem->size = size;
	new_elem->arr = arr;
	return(new_elem);
}

int	matrix_elem(t_list	*input, int x, int y)
{
	int		m_elem;
	t_int	*elem;
	t_list	*p;

	elem = NULL;
	p = ft_lstelem(input, x);
	if (p != NULL)
		elem = p->content;
	if ((elem != NULL) && (y < elem->size))
		m_elem = (elem->arr)[y];
	else
		m_elem = 0;
	return (m_elem);
}