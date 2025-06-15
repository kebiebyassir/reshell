#include "printf.h"

int	ft_putchar(int c)
{
	write(2, &c, 1);
	return (1);
}