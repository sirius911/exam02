#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

typedef struct		s_conv
{
	int width;
	int prec;
	int dot;
	char conv;
	char *base;
}					t_conv;

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr_n(char *str, int len)
{
	int i = 0;
	while (str[i] && i < len)
	{
		ft_putchar(str[i]);
		i++;
	}
}

int		ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

void	print_pad(char c, int len)
{
	while (len-- > 0)
		ft_putchar(c);
}

int		max(int a, int b)
{
	return (a > b ? a : b);
}

int		min(int a, int b)
{
	return (a < b ? a : b);
}

int		is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int		is_conv(char c)
{
	return (c == 'd' || c == 's' || c == 'x');
}

int		get_len(long long nb, int base_len)
{
	int len = 0;
	if (nb == 0)
		len++;
	while (nb > 0)
	{
		nb = nb / base_len;
		len++;
	}
	return (len);
}

void	itoa_base(long long nb, char *base, int base_len)
{
	if (nb < base_len)
	{
		ft_putchar(base[nb]);
		return ;
	}
	itoa_base(nb / base_len, base, base_len);
	ft_putchar(base[nb % base_len]);
}

int		ft_atoi(const char **str)
{
	int res = 0;
	while (is_digit(*(*(str))))
	{
		res = res * 10 + *(*str) - '0';
		(*str)++;
	}
	return (res);
}

t_conv	init(const char *str, char conv)
{
	t_conv c;
	c.width = 0;
	c.prec = -1;
	c.dot = 0;
	c.conv = conv;
	if (c.conv == 'x')
		c.base = "0123456789abcdef";
	else
		c.base = "0123456789";
	c.width = ft_atoi(&str);
	if (*str++ == '.')
	{
		c.dot = 1;
		c.prec = ft_atoi(&str);
	}
	return (c);
}

int		format(t_conv c, va_list ap)
{
	char *s;
	int len = 0;
	if (c.conv == 's')
	{
		s = va_arg(ap, char *);
		if (!s)
			s = "(null)";
		len = ft_strlen(s);
		if (c.prec == -1)
			c.prec = len;
		len = min(c.prec, len);
		print_pad(' ', c.width - len);
		ft_putstr_n(s, len);
		len = max(c.width, len);
		return (len);
	}
	long long nb;
	int neg = 0;
	if (c.conv == 'x')
		nb = va_arg(ap, unsigned int);
	if (c.conv == 'd')
		nb = va_arg(ap, int);
	if (nb < 0)
	{
		neg = 1;
		nb = -nb;
		if (c.dot == 1)
			c.prec++;
	}
	len = get_len(nb, c.conv == 'x' ? 16 : 10) + neg;
	if (c.prec == 0 && nb == 0)
		len = 0;
	print_pad(' ', c.width - max(c.prec, len));
	if (neg)
		ft_putchar('-');
	print_pad('0', c.prec - len);
	if (!(c.prec == 0 && nb == 0))
			itoa_base(nb, c.base, c.conv == 'x' ? 16 : 10);
	len = max(c.prec, len);
	len = max(c.width, len);
	return (len);
}

int		ft_printf(const char *str, ...)
{
	va_list ap;
	int i = 0; int j = 0;
	int final_len = 0;

	va_start(ap, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			j = i + 1;
			while (!is_conv(str[i]))
				i++;
			if (is_conv(str[i]))
				final_len += format(init(str + j, str[i]), ap);
		}
		else
		{
			ft_putchar(str[i]);
			final_len++;
		}
		i++;
	}
	return (final_len);
}

int main()
{
	ft_printf("%10.1s\n", "coucou");
	ft_printf("%10s\n", "coucou");
}
