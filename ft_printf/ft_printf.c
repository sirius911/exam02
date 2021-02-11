#include "ft_printf.h"

static int 	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

static void	ft_putchar(char c)
{
	write (1, &c, 1);
}

static int		ft_putnchar(const char c, const int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		ft_putchar(c);
		i++;
	}
	return (i);
}

static int 		ft_strlen(char *str)
{
	int 	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char		*ft_strchr(const char *str, int c)
{
	char	*s;

	s = (char *)str;
	while (*s)
	{
		if (*s == (char)c)
			return (s);
		s++;
	}
	if (c == 0)
		return (s);
	return (NULL);
}

int			ft_len_nbr_base(long nbr, char *base)
{
	int		i;
	int		len_base;

	i = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
		nbr = -nbr;
	len_base = ft_strlen(base);
	if (len_base == 0)
		return (0);
	while (nbr > 0)
	{
		i++;
		nbr /= len_base;
	}
	return (i);
}

int			ft_print_nbr_base(long nbr, char *base)
{
	int		i;
	int		len_base;

	i = 0;
	len_base = ft_strlen(base);
	if (nbr >= len_base)
	{
		ft_print_nbr_base(nbr / len_base, base);
		ft_print_nbr_base(nbr % len_base, base);
	}
	else
		ft_putchar(base[nbr % len_base]);
	return (ft_len_nbr_base(nbr, base));
}


static int			ft_atoi(const char *str)
{
	long int	result;
	int			sign;
	int			i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' ||
		str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if(str[i] == '-')
	{
		sign = -1;
		i++;
	}
	sign = (str[i] == '-') ? -1 : 1;
	while (ft_isdigit(str[i]))
		result = (result * 10) + str[i++] - '0';
	result = ((int)(sign * result));
	return (result);
}

static void	flags_init(t_flags *flags)
{
	flags->zero = 0;
	flags->left = 0;
	flags->precision = -1;
	flags->width = 0;
}

static int	padding(t_flags *flags, const char *format, va_list param)
{
	int		i;
	int		arg_width;

	i = 0;
	arg_width = 0;
	if (ft_isdigit(format[i]))
		flags->width = ft_atoi(&format[i]);
	else
	{
		arg_width = (int)va_arg(param, int);
		if (arg_width < 0)
		{
			arg_width = -arg_width;
			flags->left = 1;
			flags->zero = 0;
		}
		flags->width = arg_width;
		return (1);
	}
	while (ft_isdigit(format[i]))
		i++;
	return (i);
}

static int	precision(t_flags *flags, const char *format, va_list param)
{
	int		i;
	int		arg_precis;

	i = 1;
	arg_precis = 0;
	if (ft_isdigit(format[i]))
	{
		flags->precision = ft_atoi(&format[i]);
		if (flags->precision < 0)
			flags->precision = -1;
	}
	else if (format[i] == '*')
	{
		arg_precis = (int)va_arg(param, int);
		if (arg_precis < 0)
			flags->precision = -1;
		else
			flags->precision = arg_precis;
		return (i + 1);
	}
	else
		flags->precision = 0;
	while (ft_isdigit(format[i]))
		i++;
	return (i);
}

static int			ft_set_flags(t_flags *flags, const char *format, va_list param)
{
	int		i;

	i = 1;
	flags_init(flags);
	while ((ft_isdigit(format[i]) || ft_strchr("-*.", format[i])) && format[i])
	{
		if (format[i] == '0' && !flags->left)
		{
			flags->zero = 1;
			i++;
		}
		else if (format[i] == '-')
		{
			flags->zero = 0;
			flags->left = 1;
			i++;
		}
		else if (ft_isdigit(format[i]) || format[i] == '*')
			i += padding(flags, &(format[i]), param);
		else if (format[i] == '.')
			i += precision(flags, &(format[i]), param);
	}
	return (i);
}

int					ft_putx(t_flags *flags, va_list param, char *base)
{
	int				i;
	unsigned int	nbr;
	int				len;
	int				len_hex;

	i = 0;
	len = 0;
	nbr = (unsigned int)va_arg(param, unsigned int);
	len_hex = ft_len_nbr_base(nbr, base);
	len = (flags->precision > len_hex) ? flags->precision : len_hex;
	if (flags->precision == 0 && nbr == 0)
		return (i += ft_putnchar(' ', flags->width));
	if (flags->left == 0 && (flags->zero == 0 || flags->precision != -1))
		i += ft_putnchar(' ', flags->width - len);
	if (flags->zero == 1 && flags->precision == -1)
		i += ft_putnchar('0', flags->width - len);
	if (flags->precision > len_hex)
		i += ft_putnchar('0', flags->precision - len_hex);
	i += ft_print_nbr_base(nbr, base);
	if (flags->left == 1)
		i += ft_putnchar(' ', flags->width - len);
	return (i);
}

static int	ft_print_s(char *str, t_flags *flags, int len)
{
	int		i;

	i = 0;
	if (flags->precision == 0)
	{
		i += ft_putnchar(' ', len);
		return (i);
	}
	else if (flags->precision > 0)
	{
		while (i < flags->precision && str[i])
		{
			ft_putchar(str[i]);
			i++;
		}
		return (i);
	}
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
	return (i);
}

int			ft_puts(t_flags *flags, va_list param)
{
	int		i;
	char	*str;
	int		len;

	i = 0;
	str = va_arg(param, char *);
	if (!str)
		str = "(null)";
	len = ft_strlen(str);
	if (flags->precision >= 0 && flags->precision < len)
		len = flags->precision;
	if (flags->left)
	{
		i += ft_print_s(str, flags, len);
		i += ft_putnchar(' ', flags->width - len);
	}
	else
	{
		if (flags->zero)
			i += ft_putnchar('0', flags->width - len);
		else
			i += ft_putnchar(' ', flags->width - len);
		i += ft_print_s(str, flags, len);
	}
	return (i);
}

static int			print_moins(int nbr)
{
	if (nbr < 0)
	{
		ft_putchar('-');
		return (1);
	}
	return (0);
}

static int			len_nbr(int nbr)
{
	int				i;
	unsigned int	nb;

	i = 1;
	if (nbr < 0)
		nb = -nbr;
	else
		nb = nbr;
	while (nb >= 10)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

static int			ft_print_long(long nbr)
{
	int				i;

	i = 0;
	if (nbr < 0)
		nbr = -nbr;
	if (nbr >= 10)
	{
		ft_print_long(nbr / 10);
		ft_print_long(nbr % 10);
	}
	else
		ft_putchar(nbr + '0');
	return (len_nbr(nbr));
}

int					ft_putdi(t_flags *flags, va_list param)
{
	int				i;
	int				nbr;
	int				len;
	int				len_nosign;

	i = 0;
	len = 0;
	nbr = (int)va_arg(param, int);
	len_nosign = len_nbr(nbr);
	if (nbr < 0)
		flags->width--;
	len = (flags->precision > len_nosign) ? flags->precision : len_nosign;
	if (flags->precision == 0 && nbr == 0)
		return (i += ft_putnchar(' ', flags->width));
	if (flags->left == 0 && (flags->zero == 0 || flags->precision != -1))
		i += ft_putnchar(' ', flags->width - len);
	i += print_moins(nbr);
	if (flags->zero == 1 && flags->precision == -1)
		i += ft_putnchar('0', flags->width - len);
	if (flags->precision > len_nosign && flags->precision != -1)
		i += ft_putnchar('0', flags->precision - len_nosign);
	i += ft_print_long(nbr);
	if (flags->left == 1)
		i += ft_putnchar(' ', flags->width - len);
	return (i);
}

static int		ft_print_arg(const char *format, t_flags *flags, va_list param)
{
	int			i;

	i = 0;

	if (*format == 's')
		i += ft_puts(flags, param);
	else if (*format == 'd' || *format == 'i')
		i += ft_putdi(flags, param);
	else if (*format == 'x')
		i += ft_putx(flags, param, "0123456789abcdef");
	return (i);
}

int				ft_printf(const char *format, ...)
{
	va_list		param;
	size_t		written_char;
	int			i;
	t_flags		*flags;

	va_start(param, format);
	flags = malloc(sizeof(t_flags));
	written_char = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] != '%' && (written_char += 1))
			ft_putchar(format[i]);
		else
		{
			i += ft_set_flags(flags, &(format[i]), param);
			written_char += ft_print_arg(&(format[i]), flags, param);
		}
		if (format[i])
			i++;
	}
	free(flags);
	va_end(param);
	return (written_char);
}
