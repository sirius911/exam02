/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 10:33:47 by clorin            #+#    #+#             */
/*   Updated: 2021/03/09 09:17:15 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static int	ft_strlen(char *str)
{
	int		i = 0;

	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

static int	is_exist(char *str, char c, int until)
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
		while (argv[1][i])
		{
			c = argv[1][i];
			if (!is_exist(argv[1], c, i - 1))
				write (1, &c, 1);
			i++;
		}
		j = 0;
		while (argv[2][j])
		{
			c = argv[2][j];
			if (!is_exist(argv[1], c, ft_strlen(argv[1]) - 1) && !is_exist(argv[2], c, j - 1))
				write (1, &c, 1);
			j++;
		}
	}
	write (1, "\n", 1);
	return (0);
}
