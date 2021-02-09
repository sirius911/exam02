#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int	get_next_line(int fd, char **line);

int	main(int argc, char **argv)
{
	char	*line = NULL;
	int	result = 1;
	int	fd = 0;
	if (argc == 2)
		fd = open(argv[1],O_RDONLY);
	while(result != 0)
	{
		result = get_next_line(fd, &line);
		printf("%s\n", line);
		free(line);
	}
	close(fd);
	return (0);
}
