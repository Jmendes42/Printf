/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmendes <jmendes@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 00:45:45 by jmendes           #+#    #+#             */
/*   Updated: 2022/09/29 02:31:15 by jmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static int	counter(unsigned long long n, int base)
{
	int	index;

	if (n == 0)
		return (1);
	index = 0;
	while (n > 0)
	{
		n = n / base;
		index++;
	}
	return (index);
}

char	*convert(unsigned long long n, int base)
{
	char				*temp;
	unsigned long long	nr;
	int					index;

	index = counter(n, base);
	temp = (char *)malloc(sizeof(char) * (index + 1));
	temp[index--] = '\0';
	nr = n;
	if (n == 0)
		temp[0] = '0';
	while (nr > 0)
	{
		if ((nr % base) < 10)
			temp[index] = nr % base + '0';
		else
			temp[index] = nr % base + 55;
		nr = nr / base;
		index--;
	}
	return (temp);
}

void	tolower1(char *s, t_lista *s_st)
{
	while (*s != '\0')
	{
		if (*s >= 'A' && *s <= 'Z')
			*s += 32;
		if (s_st->p == 1)
			s_st->c += ft_putchar_fd(*s);
		s++;
	}
}

void	precision_unsigned(int precision, int len, t_lista *s_st)
{
	while (precision > len)
	{
		s_st->c += ft_putchar_fd('0');
		len++;
	}
}
