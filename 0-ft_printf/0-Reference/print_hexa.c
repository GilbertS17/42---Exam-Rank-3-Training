/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsahyoun <gsahyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:57:07 by gsahyoun          #+#    #+#             */
/*   Updated: 2025/10/15 18:25:26 by gsahyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	hexa_len(unsigned int value)
{
	int	len;

	len = 0;
	while (value != 0)
	{
		value /= 16;
		len++;
	}
	return (len);
}

static char	*hexa_to_str(unsigned int value, int len)
{
	char	*str;

	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		if ((value % 16) < 10)
			str[len] = (value % 16) + '0';
		else
			str[len] = (value % 16) + 87;
		value /= 16;
	}
	return (str);
}

int	print_hexa(unsigned int value)
{
	char	*str;
	int		count;
	int		len;

	if (value == 0)
		return (print_char('0'));
	len = hexa_len(value);
	str = hexa_to_str(value, len);
	if (!str)
		return (0);
	ft_putstr_fd(str, 1);
	count = ft_strlen(str);
	free(str);
	return (count);
}
