#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

int	main(int argc, char **argv)
{
	char	*line = NULL;
	int	result = 1;
	int	fd = 0;
	while(result != 0)
	{
		result = get_next_line(&line);
		printf("%s\n", line);
		free(line);
	}
	close(fd);
	return (0);
}
