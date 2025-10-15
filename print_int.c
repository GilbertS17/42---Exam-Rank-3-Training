/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr_int.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsahyoun <gsahyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:56:12 by gsahyoun          #+#    #+#             */
/*   Updated: 2025/06/11 17:15:26 by gsahyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	count_digits(int n)
{
	int				count;
	unsigned int	num;

	count = 0;
	if (n < 0)
	{
		count++;
		num = -n;
	}
	else
		num = n;
	if (n == 0)
		return (1);
	while (num > 0)
	{
		num /= 10;
		count++;
	}
	return (count);
}

int	print_int(int n)
{
	int	len;

	len = count_digits(n);
	ft_putnbr_fd(n, 1);
	return (len);
}
