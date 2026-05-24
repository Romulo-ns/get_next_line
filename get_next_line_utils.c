/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romdo-na <romdo-na@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 18:48:37 by romdo-na          #+#    #+#             */
/*   Updated: 2026/05/23 19:52:11 by romdo-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)&s[i]);
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_size;
	char	*ptr;
	size_t	i;
	size_t	j;

    if (!s1)
	    s1 = "";
	total_size = ft_strlen(s1) + ft_strlen(s2);
	ptr = malloc(sizeof(char) * (total_size + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s1))
	{
		ptr[i] = s1[i];
		i++;
	}
	j = 0;
	while (i < total_size)
	{
		ptr[i] = s2[j];
		i++;
		j++;
	}
	ptr[i] = '\0';
	return (ptr);
}
char	*ft_strdup(const char *s)
{
	int		i;
	int		size;
	char	*ptr;

	size = ft_strlen(s);
	ptr = malloc(sizeof(char) * (size + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
