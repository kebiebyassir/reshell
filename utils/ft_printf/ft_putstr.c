#include "printf.h"

int	ft_putstr(char *str)
{
	int len;

	len = 0;
	if (str == NULL)
		str = "(null)";
	while (str[len])
	{
		ft_putchar(str[len]);
		len++;
	}
	return (len);
}