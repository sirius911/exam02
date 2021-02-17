/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 11:03:31 by clorin            #+#    #+#             */
/*   Updated: 2021/02/16 08:46:43 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while(str[i])
		i++;
	return (i);
}

int		nl(char *str)
{
	int	i;

	i = 0;
	if(!str)
		return (0);
	while(str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char		*ft_strjoin(char *s1, char *s2)
{
	int	i;
	int	j;
	char	*dest;

	i = 0;
	dest = (char*)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!dest)
	{
		free(s1);
		return (NULL);
	}
	while (s1 && s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		dest[i++] = s2[j++];
	dest[i] = '\0';
	free(s1);
	return (dest);
}
char		*recup_line(char *str)
{
	int		i;
	char	*dest;

	i = 0;
	if (!str)
	{
		dest = (char*)malloc(sizeof(char));
		dest[0] = '\0';
		return (dest);
	}
	while (str[i] && str[i] != '\n')
		i++;
	dest = (char*)malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char		*save_static(char *str)
{
	int	i;
	int	j;
	char	*dest;
	
	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	dest = (char*)malloc(sizeof(char) * (ft_strlen(str) - i));
	if (!dest)
	{
		free(str);
		return (NULL);
	}
	i++;
	j = 0;
	while (str[i])
		dest[j++] = str[i++];
	dest[j] = '\0';
	free (str);
	return (dest);
}

int	get_next_line(char **line)
{
	char		buffer[1024];
	static char	*str_static = NULL;
	int		r;
	int		result;

	r = 1;
	if (!line)
		return (-1);
	while (!nl(str_static) && r != 0)
	{
		r = read(0, buffer, 1022);
		if (r == -1)
			return (-1);
		buffer[r] = '\0';
		str_static = ft_strjoin(str_static, buffer);
	}
	*line = recup_line(str_static);
	str_static = save_static(str_static);
	result = (r == 0 && ft_strlen(str_static) == 0) ? 0 : 1;
	if (result == 0)
		free(str_static);
	return (result);
}
