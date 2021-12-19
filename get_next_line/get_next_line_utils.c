/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 13:54:38 by oipadeol          #+#    #+#             */
/*   Updated: 2021/09/29 19:10:18 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t					i;
	unsigned char			uc;
	const unsigned char		*string;		

	string = (unsigned char *) s;
	uc = (unsigned char) c;
	if (n <= 0)
		return (NULL);
	i = 0;
	while ((string[i] != uc) && (i < (n - 1)))
		i++;
	if (string[i] == uc)
		return ((void *)(string + i));
	else
		return (NULL);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (i <= dstsize - 1)
	{
		if (i == dstsize - 1)
			dst[i] = '\0';
		else
			dst[i] = src[i];
		if (src[i] == '\0')
			break ;
		i++;
	}
	return (ft_strlen(src));
}

char	*fp_strjoin(char const *s1, char const *s2, size_t s2len)
{
	int			s1len;
	int			k;
	size_t		l;
	char		*newstr;

	k = 0;
	l = 0;
	s1len = ft_strlen(s1);
	newstr = (char *) malloc(s1len + s2len + 1);
	if (newstr == NULL)
		return (NULL);
	while (s1[k])
	{
		newstr[k] = s1[k];
		k++;
	}
	while (l < s2len)
	{
		newstr[k + l] = s2[l];
		l++;
	}
	newstr[k + l] = '\0';
	return (newstr);
}

char	*ft_strdup(const char *string1)
{
	char	*string2;
	int		i;

	i = 0;
	while (string1[i] != '\0')
		i++;
	string2 = (char *) malloc(i + 1);
	if (string2 == NULL)
		return (NULL);
	i = 0;
	while (string1[i])
	{
		string2[i] = string1[i];
		i++;
	}
	string2[i] = '\0';
	return (string2);
}
