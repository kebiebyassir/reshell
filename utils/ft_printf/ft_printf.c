#include "printf.h"

static int	check(const char format, va_list arg)
{
	int	len;

	len = 0;
	len = 0;
	if (format == 'c')
		len += ft_putchar(va_arg(arg, int));
	else if (format == 's')
		len += ft_putstr(va_arg(arg, char *));
	else if (format == 'p')
		len += ft_putptr(va_arg(arg, unsigned long));
	else if (format == 'd' || format == 'i')
		len += ft_putnbr(va_arg(arg, int));
	else if (format == 'u')
		len += ft_putunbr(va_arg(arg, unsigned int));
	else if (format == 'x' || format == 'X')
		len += ft_puthex(va_arg(arg, unsigned int), format);
	else if (format == '%')
		len += ft_putchar('%');
	else
	{
		len += ft_putchar('%');
		len += ft_putchar(format);
	}
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list arg;
	int i;
	int len;

	len = 0;
	i = 0;
	if (!format)
		return (-1);
	va_start(arg, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i += 1;
			if (!format[i])
				return (-1);
			len += check(format[i], arg);
		}
		else
			len += ft_putchar(format[i]);
		i++;
	}
	va_end(arg);
	return (len);
}