#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


//libft functions
char *ft_strchr(char *str, int c)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return (char *)&str[i];
		i++;
	}
	if (str[i] == (char)c)
		return (char *)&str[i];
	return NULL;
}

int ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return i;
}

void ft_putchar_fd (int c, int fd)
{
	write(fd, &c, 1);
}

void ft_putstr_fd (char *str, int fd)
{
	int i = 0;

	while (i < ft_strlen(str))
	{
		ft_putchar_fd(str[i], fd);
		i++;
	}
}

void ft_putnbr_fd (int nb, int fd)
{
	if (nb == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (nb < 0)
	{
		write (fd, "-", 1);
		nb = -nb;
	}
	if (nb >= 10)
		ft_putnbr_fd(nb / 10, fd);
	ft_putchar_fd((nb % 10) + '0', fd);
}

// print char

int print_char (int c)
{
	return (write(1, &c, 1),1);
}


//print string

int print_str(char *str)
{
	if (!str)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	ft_putstr_fd(str, 1);
	return (ft_strlen(str));
}

//print integer

int ft_intlen (int nbr)
{
	int i = 0;
	if (nbr < 0)
	{
		nbr *= -1;
		i++;
	}
	if (nbr == 0)
		return 1;
	while (nbr > 0)
	{
		i++;

		nbr /= 10;
	}
	return i;
}

int print_int (int nbr)
{
	int len = ft_intlen(nbr);
	ft_putnbr_fd(nbr, 1);
	return len;
}

//print hex

int ft_hexlen(unsigned int str)
{
	int i = 0;
	while (str != 0)
	{
		i++;
		str /= 16;
	}
	return i;
}

char *hex_to_str(unsigned int str, int len)
{
	char *str = (char *)malloc (sizeof(char) * len + 1)
}

int print_hex (unsigned int str)
{
	int len = ft_hexlen(str);
	if (str == 0)
		return print_char(0);
	char *str = hex_to_str(str, len);
}


//main.c

int main (void)
{
	print_int(-90);
	return 0;
}

int ft_printf(const char *format, ... )
{
	int i = 0;
	va_list argv;

	va_start (argv, format);
	if (!format)
		return 0;
	while (*format)
	{

		format++;
	}
}