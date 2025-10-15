/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsahyoun <gsahyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 14:10:20 by gsahyoun          #+#    #+#             */
/*   Updated: 2025/10/15 18:36:50 by gsahyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	check_type(const char *input, va_list args)
{
	int	i;

	i = 0;
	if (*input == 's')
		i += print_string(va_arg(args, char *));
	else if (*input == 'd' || *input == 'i')
		i += print_int(va_arg(args, int));
	else if (*input == 'x')
		i += print_hexa(va_arg(args, unsigned int));
	return (i);
}

int	ft_printf(const char *format, ...)
{
	va_list			args;
	unsigned int	i;

	i = 0;
	va_start(args, format);
	if (!format)
		return (0);
	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;
			if (ft_strchr("sdix", *format))
				i += check_type(format, args);
			else if (*format == '%')
				i += print_char('%');
		}
		else
			i = i + print_char(*format);
		format++;
	}
	va_end(args);
	return (i);
}

// #include <stdio.h>
// #include <limits.h>

// // declare ft_printf prototype
// int ft_printf(const char *format, ...);

// int main(void)
// {
//     int len1, len2;

//     printf("=== STRING TESTS ===\n");
//     len1 = ft_printf("ft: str: [%s]\n", "hello");
//     len2 = printf("og: str: [%s]\n", "hello");
//     printf("Lengths: ft=%d, og=%d\n\n", len1, len2);

//     len1 = ft_printf("ft: empty str: [%s]\n", "");
//     len2 = printf("og: empty str: [%s]\n", "");
//     printf("Lengths: ft=%d, og=%d\n\n", len1, len2);

//     len1 = ft_printf("ft: null str: [%s]\n", (char *)NULL);
//     len2 = printf("og: null str: [%s]\n", (char *)NULL);
//     printf("Lengths: ft=%d, og=%d\n\n", len1, len2);

//     printf("=== INTEGER TESTS ===\n");
//     len1 = ft_printf("ft: int: [%d] [%i]\n", 12345, -12345);
//     len2 = printf("og: int: [%d] [%i]\n", 12345, -12345);
//     printf("Lengths: ft=%d, og=%d\n\n", len1, len2);

//     len1 = ft_printf("ft: int zero: [%d]\n", 0);
//     len2 = printf("og: int zero: [%d]\n", 0);
//     printf("Lengths: ft=%d, og=%d\n\n", len1, len2);

//     len1 = ft_printf("ft: int limits: [%d] [%i]\n", INT_MIN, INT_MAX);
//     len2 = printf("og: int limits: [%d] [%i]\n", INT_MIN, INT_MAX);
//     printf("Lengths: ft=%d, og=%d\n\n", len1, len2);

//     printf("=== HEXADECIMAL TESTS ===\n");
//     len1 = ft_printf("ft: hex lower: [%x]\n", 3735928559U);
//     len2 = printf("og: hex lower: [%x]\n", 3735928559U);
//     printf("Lengths: ft=%d, og=%d\n\n", len1, len2);

//     len1 = ft_printf("ft: hex zero: [%x]\n", 0);
//     len2 = printf("og: hex zero: [%x]\n", 0);
//     printf("Lengths: ft=%d, og=%d\n\n", len1, len2);

//     return 0;
// }
