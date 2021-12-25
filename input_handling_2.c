/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 06:25:49 by oipadeol          #+#    #+#             */
/*   Updated: 2021/12/22 20:28:41 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	int	i;
	int	len;
	t_int	*elem;

	i = 0;
	while (lst != NULL)
	{
		elem = lst->content;
		len = elem->size;
		while (i++ < len)
		{
			ft_putnbr_fd((elem->arr)[i - 1], 1);
			ft_putchar_fd(' ', 1);
		}
		i = 0;
		ft_putchar_fd('\n', 1);
		lst = lst->next;
	}	
}

t_list	*input_lines(int argc, char **argv)
{
	t_list	*input;
	int		fd;
	char	*map_string;
	t_int	*t_map_int;

	fd = check_input_get_fd(argc, argv);
	map_string = get_next_line(fd);
	t_map_int = str_to_int(map_string);
	input = ft_lstnew(t_map_int);
	while (map_string)
	{
		free(map_string);
		map_string = get_next_line(fd);
		if (map_string)
		{
			t_map_int = str_to_int(map_string);
			ft_lstadd_back(&input, ft_lstnew(t_map_int));
		}
	}	
	check_equal_size(input);
	print_all(input);
	return (input);
}
