




#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>




typedef struct s_list
{
	int id;
	int written;
	int width;
	int precision;
} 	t_list;

/////////////////// UTILS ////////////////////////////

void init_flags(t_list *flags)
{
	flags->id = 0;
	flags->precision = 0;
	flags->width = 0;
}


static void	ft_putchar_inc(char c, t_list *flags)
{
	write(1, &c, 1);
	flags->written++;
}

static int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

static int count_digits (long n)
{
	int i;

	i = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static int count_hex (long n)
{
	int i;

	i = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n = n / 16;
		i++;
	}
	return (i);
}

static int is_in_charset(char c, char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

//////////////////////////////// FLAG PARSING ////////////////////////////////

static int	parse_flags(const char *fmt, t_list *flags)
{
	int i;
	int atoi;

	i = 1;
	atoi = 0;
	init_flags(flags);
	while (is_in_charset(fmt[i], "0123456789"))
	{
		atoi = atoi * 10 + fmt[i] - 48;
		i++;
	}
	flags->width = atoi;
	atoi = 0;
	if (fmt[i] == '.')
	{
		i++;
		while (is_in_charset(fmt[i], "0123456789"))
		{
			atoi = atoi * 10 + fmt[i] - 48;
			i++;
		}
		if (atoi == 0)
			atoi = -1;
		flags->precision = atoi;
	}
	if (is_in_charset(fmt[i], "sdx"))
	{
		flags->id = fmt[i];
		i++;
		return (i);
	}
	return (0);
}

/////////////////////////////// PRINT ARGS //////////////////////////////////

// ---------------------------- strings -------------------------------------

static void ft_putstr(char *str, t_list *flags)
{
	int i;
	int len;

	if (!str)
		str = "(null)";
	i = 0;
	len = ft_strlen(str);
	if (flags->precision == -1)
		len = 0;
	if (flags->precision > 0 && flags->precision < len)
		len = flags->precision;
	if (flags->width > len)
	{
		flags->width -= len;
		while (flags->width > 0)
		{
			ft_putchar_inc(' ', flags);
			flags->width--;
		}
	}
	while (str[i] && i < len)
	{
		ft_putchar_inc(str[i], flags);
		i++;
	}
}


// -------------------------------- hex -----------------------------------
static void ft_puthex(long n, t_list *flags)
{
	char *base;

	base = "0123456789abcdef";
	if (n > 15)
		ft_puthex(n / 16 , flags);
	ft_putchar_inc(base[n % 16], flags);
}

static void ft_hexa(long n, t_list *flags)
{
	int len;
	int precision_minus_len;
	len = count_hex(n);

	precision_minus_len = 0;
	if (flags->precision > 0 && flags->precision > len)
	{
		precision_minus_len = flags->precision - len;
		len = flags->precision;
	}
	if (flags->width > 0 && flags->width > len)
	{
		flags->width -= len;
		while (flags->width > 0)
		{
			ft_putchar_inc(' ', flags);
			flags->width--;
		}
	}
	if (n < 0)
		ft_putchar_inc('-', flags);
	while (precision_minus_len > 0)
	{
		ft_putchar_inc('0', flags);
		precision_minus_len--;
	}

	if (!(flags->precision == -1 && n == 0))
		ft_puthex(n, flags);

}

// ----------------------------------- decimal ----------------------------

static void ft_putnbr(long n, t_list *flags)
{
	if (n < 0)
		n = -n;
	if (n > 9)
		ft_putnbr(n / 10 , flags);
	ft_putchar_inc(n % 10 + 48, flags);
}

static void ft_number(long n, t_list *flags)
{
	int len;
	int precision_minus_len;
	len = count_digits(n);
	precision_minus_len = 0;
	if (flags->precision == -1)
		len = 0;
	else if (flags->precision > 0 && flags->precision > len)
	{
		precision_minus_len = flags->precision - len;
		len = flags->precision;
	}
	if (flags->width > 0 && flags->width > len)
	{
		flags->width = flags->width - len - (n < 0);
		while (flags->width)
		{
			ft_putchar_inc(' ', flags);
			flags->width--;
		}
	}
	if (n < 0)
		ft_putchar_inc('-', flags);
	while (precision_minus_len > 0)
	{
		ft_putchar_inc('0', flags);
		precision_minus_len--;
	}
	if (!(flags->precision == -1 && n == 0))
	ft_putnbr(n, flags);

}


///////////////////////////////////// FETCH ARGS /////////////////////////////

static void print_flags(va_list ap, t_list *flags)
{
	if (flags->id == 'd')
		ft_number(va_arg(ap, int), flags);
	if (flags->id == 's')
		ft_putstr(va_arg(ap, char*), flags);
	if (flags->id == 'x')
		ft_hexa(va_arg(ap, unsigned int), flags);

}


//////////////////////////////// MAIN FUNCTION ///////////////////////////////

int		ft_printf(const char *fmt, ...)
{
	va_list ap;
	t_list *flags;
	int i;
	int is_valid_flag;
	int res;

	res = 0;
	i = 0;
	is_valid_flag = 0;
	va_start(ap, fmt);
	if (!(flags = malloc(sizeof(t_list))))
		return (0);
	init_flags(flags);
	flags->written = 0;
	while (fmt[i])
	{
		is_valid_flag = 0;
		if (fmt[i] == '%' && fmt[i + 1])
		{
			is_valid_flag = parse_flags(&fmt[i], flags);
			if (is_valid_flag)
			{
				print_flags(ap, flags);
				i = i + is_valid_flag;
			}
			else
			{
				ft_putchar_inc(fmt[i], flags);
				i++;
			}
		}
		else
		{
			ft_putchar_inc(fmt[i], flags);
			i++;
		}
	}
	res = flags->written;
	va_end(ap);
	free(flags);
	return (res);

}
