/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 18:51:48 by oipadeol          #+#    #+#             */
/*   Updated: 2021/12/21 10:30:16 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_error(void)
{
	write(STDERR_FILENO, "Error\n", 6);
	exit(1);
}

int	check_equal_size(t_list *input)
{
	int		len;
	t_int	*elem;

	elem = input->content;
	len = elem->size;
	while (input != NULL)
	{
		elem = input->content;
		if (elem->size != len)
			ft_error();
		input = input->next;
	}
	return (1);	
}

static int	do_atoi(const char *str)
{
	int		i;
	long	num;
	int		sign;

	i = 0;
	num = 0;
	sign = 1;
	if (str[0] == '\0')
		return (0);
	while (ft_strchr(" \n\t\v\f\r", str[i]))
		i++;
	if ((str[i] == '-') || (str[i] == '+'))
		if (str[i] == '-')
			sign = (-1);
	if ((str[i] == '-') || (str[i] == '+'))
		i++;
	while ((str[i] > 47) && (str[i] < 58))
	{
		num = (num * 10) + (str[i] - 48);
		if (((num > INT_MAX) || ((num * sign) < INT_MIN))
			&& (num * sign != INT_MIN))
			ft_error();
		i++;
	}
	return (sign * num);
}

static void	digit_check(char *s)
{
	int	i;

	i = 0;
	while ((s[i++] != '\0') && (s[i - 1] != '\n'))
	{
		if ((!ft_isdigit(s[i - 1])) && (!(((s[i - 1] == '-')
						|| (s[i - 1] == '+')) && (i - 1 == 0))))
			ft_error();
		if ((((s[i - 1] == '-') || (s[i - 1] == '+'))
						&& ((s[i] == '\0') || (s[i] == '\n'))))
			ft_error();
	}
	i = 0;
}

t_int	*str_to_int(char *map_string)
{
	int		i;
	int		len;
	char	**ch;
	t_int	*t_arr;
	int		*arr;

	i = 0;
	ch = ft_split(map_string, ' ');
	if (ch == NULL)
		return (NULL);
	while (ch[i])
		i++;
	if (*(ch[i - 1]) == '\n')
		ch[--i] = NULL;
	arr = (int *) ft_calloc(i, sizeof(int));
	if (arr == NULL)
		return (NULL);
	len = i;
	i = 0;
	while (ch[i++])
	{
		digit_check(ch[i - 1]);
		arr[i - 1] = do_atoi(ch[i - 1]);
		free(ch[i - 1]);
	}
	free(ch);
	t_arr = ft_new_t_int(len, arr);//free arr and free t_arr
	return (t_arr);
}