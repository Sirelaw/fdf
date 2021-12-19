/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 06:25:49 by oipadeol          #+#    #+#             */
/*   Updated: 2021/12/19 12:55:43 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//this file handles input

static int	check_input_get_fd(int argc, char **argv)
{
	int	fd;
	
	if (argc != 2)
	{
		write(1, "*****************************************\n", 42);
		write(1, "*  Enter the required set of arguments. *\n", 42);
		write(1, "*Input should have the following format.*\n", 42);
		write(1, "*$>./fdf map.fdf                        *\n", 42);
		write(1, "*****************************************\n", 42);
		exit(1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror(argv[1]);
		exit(1);
	}
	return (fd);
}

void	print_all(t_list *lst)
{
	while (lst != NULL)
	{
		ft_putstr_fd("line", 1);
		ft_putchar_fd('\n', 1);
		lst = lst->next;
	}
}

t_list	*input_lines(int argc, char **argv)
{
	t_list	*input;
	int		fd;
	char	*map_string;
	
	fd = check_input_get_fd(argc, argv);
	map_string = get_next_line(fd);
ft_putstr_fd(map_string, 1);
	input = ft_lstnew(map_string);
	while (map_string)
	{
		map_string = get_next_line(fd);
ft_putstr_fd(map_string, 1);
		ft_lstadd_back(&input, ft_lstnew(map_string));
	}
	// print_all(input);
	return (input);
}