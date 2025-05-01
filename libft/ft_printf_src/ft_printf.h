#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft.h"
# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *form, ...);
int		ft_printchar(char c);
int		ft_print_digit_unsigned(unsigned int num);
int		ft_print_void(void *ptr);
int		ft_printstring(const char *s);
int		ft_print_digit(int num);
int		ft_print_digit_hex_low(unsigned int n);
int		ft_print_digit_hex_upp(unsigned int n);
int		to_hex_low(unsigned long n);
int		to_hex_upp(unsigned long n);
#endif
