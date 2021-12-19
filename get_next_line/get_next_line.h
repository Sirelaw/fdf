/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 09:29:23 by oipadeol          #+#    #+#             */
/*   Updated: 2021/09/30 14:19:41 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

// Returns a line read from a file descriptor. Calling this function in a loop
// will then allow you to read the text available on the file descriptor one
// line at a time until the end of it.
char	*get_next_line(int fd);
// Locates the first instance of c (converted to an unsigned char) in string s.
void	*ft_memchr(const void *s, int c, size_t n);
// Mallocs for and appends s2len bytes of s2 to the end of a Null-terminated
// string s1. Returns the new Null-terminated string.
char	*fp_strjoin(char const *s1, char const *s2, size_t s2len);
// copies up to dstsize - 1 characters from the string src to dst,
// NUL-terminating the result if dstsize is not 0.
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
// Returns the size of the Null-terminated string s.
size_t	ft_strlen(const char *s);
// allocates sufficient memory for a copy of the string s1, does the copy,
//and returns a pointer to it.
char	*ft_strdup(const char *string1);

#endif