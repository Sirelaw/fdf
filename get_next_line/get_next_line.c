/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 20:12:39 by oipadeol          #+#    #+#             */
/*   Updated: 2021/09/30 14:06:45 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*create_buffers(char **read_buf, char **keep, char **temp, int fd)
{
	if ((fd < 0) || (BUFFER_SIZE <= 0))
		return (NULL);
	*read_buf = (char *)malloc(BUFFER_SIZE + 1);
	if (*read_buf == NULL)
		return (NULL);
	*keep = (char *)malloc(1);
	if (*keep == NULL)
		return (NULL);
	*keep[0] = '\0';
	*temp = NULL;
	return ("");
}

void	*check_temp(char **store, char **keep, char **read_buf)
{
	char	*temp;
	char	*temp_add;

	temp = ft_memchr(*store, '\n', ft_strlen(*store));
	if (temp)
	{
		temp_add = *keep;
		*keep = fp_strjoin(*keep, *store, (temp - *store + 1));
		if (*keep == NULL)
			return (NULL);
		free(temp_add);
		temp_add = *store;
		*store = ft_strdup(temp + 1);
		free(temp_add);
		free(*read_buf);
		return (*keep);
	}
	temp_add = *keep;
	*keep = fp_strjoin(*keep, *store, ft_strlen(*store));
	if (*keep == NULL)
		return (NULL);
	free(temp_add);
	free(*store);
	*store = NULL;
	return ("");
}

void	*free_and_return(char **read_buf, char **keep, int len, int x)
{
	if ((x == 1) || (len <= 0))
	{
		free(*read_buf);
		if (ft_strlen(*keep) > 0)
			return (*keep);
		else
		{
			free(*keep);
			return (NULL);
		}
	}
	else
	{
		free(*read_buf);
		return (*keep);
	}
}

void	*read_newline(char **read_buf, char **store, char **keep, char **flag)
{
	char	*temp;
	char	*temp_add;

	temp = ft_memchr(*read_buf, '\n', ft_strlen(*read_buf));
	if (temp)
	{
		*flag = "1";
		*store = (char *)malloc(BUFFER_SIZE - (temp - *read_buf));
		if (*store == NULL)
			return (NULL);
		ft_strlcpy(*store, temp + 1, (BUFFER_SIZE - (temp - *read_buf)));
		temp_add = *keep;
		*keep = fp_strjoin(*keep, *read_buf, temp - *read_buf + 1);
		free(temp_add);
		if (*keep == NULL)
			return (NULL);
	}
	temp_add = *keep;
	if (*flag == 0)
		*keep = fp_strjoin(*keep, *read_buf, ft_strlen(*read_buf));
	if (*keep == NULL)
		return (NULL);
	if (temp_add != *keep)
		free(temp_add);
	return ("\0");
}

/*	read_buf;	 Buffer allocated for reading.
	store;	 Holds content of read_buff after /n is found. Static variable;
	temp;		 Used to addresses before freeing. Also used as flag.
	keep;		 Holds content of all calls to read until a \n is found.
	read_bytes:	 the number of bytes in a read call.*/

char	*get_next_line(int fd)
{
	char		*read_buf;
	static char	*store;
	char		*temp;
	char		*keep;
	int			read_bytes;

	if (!(create_buffers(&read_buf, &keep, &temp, fd)))
		return (NULL);
	if (store != NULL)
	{
		temp = check_temp(&store, &keep, &read_buf);
		if ((temp == NULL) || (ft_strlen(temp) > 0))
			return (temp);
		temp = NULL;
	}
	while (temp == NULL)
	{
		read_bytes = read(fd, read_buf, BUFFER_SIZE);
		if (read_bytes <= 0)
			return (free_and_return(&read_buf, &keep, read_bytes, 1));
		read_buf[read_bytes] = '\0';
		if (!(read_newline(&read_buf, &store, &keep, &temp)))
			return (NULL);
	}
	return (free_and_return(&read_buf, &keep, read_bytes, 2));
}
