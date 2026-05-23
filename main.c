
#include "get_next_line.h"
#include <stdio.h>

int	main(void)
{
	int		file_descriptor;
	char	*line;

	file_descriptor = open("file.txt", O_RDONLY);
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