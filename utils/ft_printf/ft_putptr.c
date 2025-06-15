#include "printf.h"

int	ft_putptr(unsigned long ptr)
{
	int len;
	char *hexa;
	char hex[16];
	int i;

	hexa = "0123456789abcdef";
	len = 0;
	if (ptr == 0)
		len += ft_putstr("(nil)");
	else
	{
		len += ft_putstr("0x");
		i = 0;
		while (ptr > 0)
		{
			hex[i++] = hexa[ptr % 16];
			ptr /= 16;
		}
		while (i > 0)
			len += ft_putchar(hex[--i]);
	}
	return (len);
}