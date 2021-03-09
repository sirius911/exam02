/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 09:42:55 by clorin            #+#    #+#             */
/*   Updated: 2021/03/09 09:09:51 by clorin           ###   ########.fr       */
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

static int	is_present(char *str, char c, int until)
{
	int	i;

	i = 0;
	while(str[i] && i <= until)
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

	i = 0;
	if (argc == 3)
	{
		while (argv[1][i])
		{
			if (!is_present(argv[1], argv[1][i], i - 1) && is_present(argv[2], argv[1][i], ft_strlen(argv[2]) - 1))
				write(1, &argv[1][i], 1);
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}
