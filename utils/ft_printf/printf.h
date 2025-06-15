#ifndef PRINTF_H
# define PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);
int	ft_putchar(int c);
int	ft_puthex(unsigned int n, char format);
int	ft_putnbr(int n);
int	ft_putptr(unsigned long ptr);
int	ft_putstr(char *str);
int	ft_putunbr(unsigned int n);

#endif