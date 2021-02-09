/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clorin <clorin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 10:55:31 by clorin            #+#    #+#             */
/*   Updated: 2021/02/09 14:58:43 by clorin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

#define BUFFER 1024
int			ft_strlen(char *str)
{
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

static	int		nl_(char *str)
{
	int		i;

	i = 0;
	if(!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char 		*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char		*dest;

	i = 0;
	if (!s2 || ft_strlen(s2) == 0)
		return (s1);
	dest = (char*)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!dest)
	{
		free (s1);
		return (NULL);
	}
	while (s1 && s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		dest[i] = s2[j];
		i++;
		j++;
	}
	free (s1);
	return (dest);
}

static	char		*recup_line(char *str)
{
	char	*dest;
	int	i;

	i = 0;
	if (!str)
	{
		dest = (char*)malloc(sizeof(char));
		dest[0] = '\0';
	}
	while (str[i] && str[i] != '\n')
		i++;
	dest = (char *)malloc(sizeof(char) * i + 1);
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

static	char		*save_static(char *str)
{
	int		i;
	int		j;
	char		*dest;
	int		len;
	
	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	len = ft_strlen(str);
	while ( str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	dest = (char*)malloc(sizeof(char) * (len - i));
	if (!dest)
	{
		free(str);
		return (NULL);
	}
	i++;
	while (str[i])
		dest[j++] = str[i++];
	dest[j] = '\0';
	free(str);
	return (dest);
}

int			get_next_line(int fd, char **line)
{
	char		buffer[1024];
	static char	*str_static = NULL;
	int		result;
	int		result_read;

	if (fd < 0 || !line || read(fd, NULL, 0) < 0)
	{
		line = NULL;
		return (-1);
	}
	result_read = 1 ;
	while (!nl_(str_static) || result_read != 0)
	{
		result_read = read(fd, buffer, 1022);
		if (result_read == -1)
		{
			line = NULL;
			return (-1);
		}
		buffer[result_read] = '\0';
		str_static = ft_strjoin(str_static, buffer);
	}
	*line = recup_line(str_static);
	str_static = save_static(str_static);
	result = (result_read == 0 && ft_strlen(str_static) == 0) ? 0 : 1;
	if (result == 0)
		free(str_static);
	return (result);
}
