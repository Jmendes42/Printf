/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmendes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 16:47:48 by jmendes           #+#    #+#             */
/*   Updated: 2021/06/21 19:03:22 by jmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "printf.h"

size_t	ft_strlen(const char *s)
{
	size_t index;

	index = 0;
	while (s[index])
		index++;
	return (index);
}

int	ft_putchar_fd(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr_fd(char *s)
{
	write(1, s, ft_strlen(s));
	return (ft_strlen(s));
}

void	ft_putnbr_fd(int n)
{
	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648");
	}
	else
	{
		if (n < 0)
		{
			ft_putchar_fd('-');
			n = n * -1;
		}
		if (n >= 10)
			ft_putnbr_fd(n / 10);
		ft_putchar_fd((n % 10) + '0');
	}
}


