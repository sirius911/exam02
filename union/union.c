/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 10:33:47 by clorin            #+#    #+#             */
/*   Updated: 2021/02/09 10:51:55 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static int	exist_in(char *str, char c, int until)
{
	int	i;

	i = 0;
	while (str[i]  && i <= until)
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int		main(int argc, char **argv)
{
	int	i;
	int	j;
	char	c;

	i = 0;
	if (argc == 3)
	{
		if (argv[1][0])
		{
			write (1, &argv[1][0], 1);
			i++;
			while (argv[1][i])
			{
				c = argv[1][i];
				if (!exist_in(argv[1], c, i - 1))
					write (1, &c, 1);
				i++;
			}
			i--;
		}
		j = 0;
		while (argv[2][j])
		{
			c = argv[2][j];
			if (!exist_in(argv[1], c, i) && !exist_in(argv[2], c, j - 1))
				write (1, &c, 1);
			j++;
		}
	}
	write (1, "\n", 1);
	return (0);
}
