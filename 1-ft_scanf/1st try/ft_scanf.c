#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
	int c;
	
	while ((c = fgetc(f)) != EOF)
	{
		if (!isspace(c))
		{
			ungetc(c, f);
			break;
		}
	}
	return (0);
}

int match_char(FILE *f, char c)
{
    int d = fgetc(f);
	if (c == d)
		return 1;
	if (d != EOF)
		ungetc(d, f);
    return (0);
}

int scan_char(FILE *f, va_list ap)
{
	int c = fgetc(f);
	if (c == EOF)
		return 0;
	char *ptr = va_arg(ap, char *);
	*ptr = (char)c;
	return (1);
}

int scan_int(FILE *f, va_list ap)
{
	int sign = 1, value = 0;
	match_space(f);
	int c = fgetc(f);
	if (!isdigit(c))
	{
		if (c != EOF)
			ungetc(c, f);
		return 0;
	}
	if (c == '-' || c == '+')
	{
		if (c == '-')
			sign = -1;
		c = fgetc(f);
	}
	while (isdigit(c))
	{
		value = value * 10 + (c - '0');
		c = fgetc(f);
	}
	if (c != EOF)
		ungetc(c, f);
	int *ptr = va_arg(ap, int *);
	*ptr = value * sign;
	return 1;
}

int scan_string(FILE *f, va_list ap)
{
	match_space(f);
	int c;
	int i = 0;
	char *str = va_arg(ap, char *);
	while ((c = fgetc(f)) != EOF && !isspace(c))
		str[i++] = (char)c;
	if (c != EOF)
		ungetc(c, f);
	str[i] = '\0';
	return i > 0 ? 1 : 0;
}


int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
			return scan_char(f, ap);
		case 'd':
			match_space(f);
			return scan_int(f, ap);
		case 's':
			match_space(f);
			return scan_string(f, ap);
		case EOF:
			return -1;
		default:
			return -1;
	}
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0;

	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (match_conv(f, &format, ap) != 1)
				break;
			else
				nconv++;
		}
		else if (isspace(*format))
		{
			if (match_space(f) == -1)
				break;
		}
		else if (match_char(f, *format) != 1)
			break;
		format++;
	}
	
	if (ferror(f))
		return EOF;
	return nconv;
}


int ft_scanf(const char *format, ...)
{
	va_list args;
    va_start(args, format);
	int ret = ft_vfscanf(stdin, format, args);
	va_end(args);
	return ret;
}
int main(void)
{
    int n;
    char s[100];
    char c;

    printf("Enter: ");
    int res = ft_scanf("%d %s %c", &n, s, &c);
    printf("Scanned %d values: n=%d s=%s c=%c\n", res, n, s, c);
    return 0;
}