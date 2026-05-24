/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romdo-na <romdo-na@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 14:21:28 by romdo-na          #+#    #+#             */
/*   Updated: 2026/05/24 14:21:29 by romdo-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	main(void)
{
	int		file_descriptor;
	char	*line;

	file_descriptor = open("text.txt", O_RDONLY);
	if (file_descriptor < 0)
		return (1);
	while ((line = get_next_line(file_descriptor)))
	{
		printf("%s", line);
		free(line);
	}
	close(file_descriptor);
	return (0);
}
