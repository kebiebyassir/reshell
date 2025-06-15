#include "printf.h"

int	ft_puthex(unsigned int n, char format)
{
	int		len;
	char	*hexa;

	hexa = NULL;
	len = 0;
	if (format == 'x')
		hexa = "0123456789abcdef";
	else if (format == 'X')
		hexa = "0123456789ABCDEF";
	if (n >= 16)
		len += ft_puthex(n / 16, format);
	len += ft_putchar(hexa[n % 16]);
	return (len);
}
