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
    {
        ungetc(c, f);
        return 0;
    }
    char *ptr = va_arg(ap, char *);
    *ptr = (char)c;
    return (1);
}

int scan_int(FILE *f, va_list ap)
{
    match_space(f);
    int sum = 0, sign = 1;
    int c = fgetc(f);
    if (sign == '-' || sign == '+')
    {
        if (sign == '-' )
            sign = -1;
        c = fgetc(f);
    }
    if (!isdigit(c))
    {
        ungetc(c, f);
        return 0;
    }
    while (isdigit(c))
    {
        sum = sum * 10 + (c - '0');
        c = fgetc(f);
    }
    if (c != EOF)
        ungetc(c, f);
    int *ptr = va_arg(ap, int *);
    *ptr = sign * sum;
    return (1);
}

int scan_string(FILE *f, va_list ap)
{
    match_space(f);
    char *ptr = va_arg(ap, char *);
    int i = 0, c;
    while ((c = fgetc(f)) != EOF && !isspace(c))
        ptr[i++] = (char)c;
    ptr[i] = '\0';
    return (i > 0 ? 1 : 0);
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
    va_list ap;
    va_start(ap, format);
    int ret = ft_vfscanf(stdin, format, ap);
    va_end(ap);
    return ret;
}

// int main (void)
// {
//     int d;
//     char c;
//     char s[100];

//     ft_scanf("%d %c %s", &d, &c, &s);
//     printf("%d %c %s\n", d, c, s);

//     return 0;
// }