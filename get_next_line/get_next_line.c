#include "get_next_line.h"
#include <stdio.h>

static int		ft_strlen(char *str)
{
	int		i = 0;

	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

static int		nl(char *str)
{
	int		i = 0;

	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char		*ft_strjoin(char *s1, char *s2)
{
	int		i = 0;
	int		j = 0;
	char		*dest;

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
	while (s2[j])
		dest[i++] = s2[j++];
	dest[i] = '\0';
	free (s1);
	return (dest);
}

static char		*recup_line(char *str)
{
	int		i = 0;
	char		*dest;

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

static char		*save_static(char *str)
{
	int		i = 0;
	int		j = 0;
	char		*dest;
	int		len = 0;

	len = ft_strlen(str);
	if(!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\0')
		return (NULL);
	dest = (char*)malloc(sizeof(char) * (len - i));
	if (!dest)
	{
		free (str);
		return (NULL);
	}
	i++;
	while(str[i])
		dest[j++] = str[i++];
	dest[j] = '\0';
	free (str);
	return (dest);
}

int			get_next_line(char **line)
{
	char		buffer[1028];
	static char	*str_static = NULL;
	int		r = 1;
	int		result;

	if (!line)
		return (-1);
	while(!nl(str_static) && r != 0)
	{
		r = read(0, buffer, 1022);
		if (r == -1)
		{
			free(str_static);
			return (-1);
		}
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
