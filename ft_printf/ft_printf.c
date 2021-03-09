#include <stdarg.h>
#include <unistd.h>

typedef struct s_flag
{
	int			width;
	int			prec;
	int			dot;
	char		conv;
}				t_flag;

static int 		ft_strlen(char *str)
{
	int 		i = 0;

	if (!str)
		return(0);
	while (str[i])
		i++;
	return(i);
}

int 			is_digit(char c)
{
	return(c >= '0' && c <= '9');
}

int				is_conv(char c)
{
	return (c == 's' || c == 'd' || c == 'x');
}

int 			max(int a, int b)
{
	return ((a > b) ? a : b);
}

int 			min(int a, int b)
{
	return ((a < b) ? a : b);
}

void 			print_nbr(long long nb, char *base)
{
	int		len_base = 0;

	len_base = ft_strlen(base);
	if (nb < len_base)
	{
		write(1, &base[nb], 1);
		return ;
	}
	print_nbr(nb / len_base, base);
	write (1, &base[nb % len_base], 1);
}

int 			ft_atoi(const char **str)
{
	int 		result = 0;

	while (is_digit(**str))
	{
		result = result * 10 + **str - '0';
		(*str)++;
	}
	return (result);
}

int 			get_len(long long nb, int len_base)
{
	int 	len = 0;

	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb = nb / len_base;
		len++;
	}
	return (len);
}

t_flag 			init_flag(const char *str, char c)
{
	t_flag		flag;
	flag.width = 0;
	flag.prec = -1;
	flag.dot = 0;
	flag.conv = c;
	flag.width = ft_atoi(&str);
	if (*str == '.')
	{
		str++;
		flag.dot = 1;
		flag.prec = ft_atoi(&str);
	}
	return (flag);
}

void			print_pad(char c, int len)
{
	while (len-- > 0)
		write (1, &c, 1);
}

void			print_str(char *str, int len)
{
	int 		i = 0;

	while (str[i] && i < len)
		write(1, &str[i++], 1);
}

int 			format(t_flag flag, va_list ap)
{
	char		*str;
	long long	nb;
	int			neg = 0;
	int 		len = 0;

	if (flag.conv == 's')
	{
		str = va_arg(ap, char*);
		if (!str)
			str = "(null)";
		len = ft_strlen(str);
		if (flag.prec == -1)
			flag.prec = len;
		len = min(flag.prec, len);
		print_pad(' ', flag.width - len);
		print_str(str, len);

		return (max(flag.width, len));
	}
	if (flag.conv == 'd')
		nb = va_arg(ap, int);
	if (flag.conv == 'x')
		nb = va_arg(ap, unsigned int);
	if (nb < 0)
	{
		neg = 1;
		nb = -nb;
		if (flag.dot == 1)
			flag.prec++;
	}
	len = get_len(nb,(flag.conv == 'd')? 10 : 16) + neg;
	if (flag.prec == 0 && nb == 0)
		len = 0;
	print_pad(' ', flag.width - max(flag.prec, len));
	if (neg)
		write(1, "-", 1);
	print_pad('0', flag.prec - len);
	if (!(flag.prec == 0 && nb == 0))
		print_nbr(nb, (flag.conv == 'd') ? "0123456789" : "0123456789abcdef");
	len = max(flag.prec, len);
	len = max(flag.width, len);
	return (len);
}

int				ft_printf(const char *str, ...)
{
	va_list		ap;
	int			i = 0;
	int			j = 0;
	int			written = 0;

	if (!str)
		return (0);
	va_start(ap, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			j = i + 1;
			while (str[i] && !is_conv(str[i]))
				i++;
			if (!str[i])
			{
				va_end(ap);
				return (written);
			}
			if (is_conv(str[i]))
				written += format(init_flag(str + j, str[i]), ap);
		}
		else
		{
			write(1, &str[i], 1);
			written++;
		}
		i++;
	}
	va_end(ap);
	return (written);
}
