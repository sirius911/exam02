#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

int	main(void)
{
	char	*line = NULL;
	int	result = 1;
	while(result != 0)
	{
		result = get_next_line(&line);
		printf("%s\n", line);
		free(line);
	}
	return (0);
}
