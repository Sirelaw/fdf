/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fdf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 10:06:14 by oipadeol          #+#    #+#             */
/*   Updated: 2021/12/30 23:05:29 by oipadeol         ###   ########.fr       */
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
	(new_node->point)[0] = row_n;
	(new_node->point)[1] = col_n;
	(new_node->point)[2] = ft_atoi(temp[0]);
	if (temp[1])
		new_node->color = ft_strtol(temp[1], NULL, 16); // work on your strtol
	if (temp[1])
		free(temp[1]);
	else
		new_node->color = 0x00FFFFFF;
	printf("%d\n", (new_node->point)[2]);
	(new_node->proj)[0] = 0;
	(new_node->proj)[1] = 0;
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