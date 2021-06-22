/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmendes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 00:45:45 by jmendes           #+#    #+#             */
/*   Updated: 2021/06/21 19:04:53 by jmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	counter(unsigned long long n, int base)
{
	int index;

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

void		convert(unsigned long long n, int base, p_lista *d_st)
{
	char *temp;
	unsigned long long	nr;
	int			index;
	index = counter(n, base);
	temp = (char *)malloc(sizeof(char) * (index + 1));
	temp[index--] = '\0';
	d_st->str = temp;
	nr = n;
	if (n == 0)
		d_st->str[0] = '0';
	while (nr > 0)
	{
		if ((nr % base) < 10)
		{
			d_st->str[index] = nr % base + '0';
		}
		else
		{
			d_st->str[index] = nr % base + 55;

		}
		nr = nr / base;
		index--;
	}
	free (temp);
}
void tolower1(char *s, p_lista *d_st)
{
	while (*s != '\0')
	{
		if (*s >= 'A' && *s <= 'Z')
			*s += 32;
		if (d_st->p == 1)
			d_st->c += ft_putchar_fd(*s);
		s++;
	}
}

void    printp(p_lista *d_st, unsigned long long n)
{
	int control;

	control = 0;
	d_st->p += 1;
	convert(n, 16, d_st);
	if (!n && d_st->precision == 0) 
		d_st->str[0] = '\0';
	if (d_st->precision > 0 && d_st->width < d_st->precision)
	{
		d_st->c += write(1, "0x", 2);
		precision(d_st->precision, ft_strlen(d_st->str), d_st, 0);
		tolower1(d_st->str, d_st);
		control += 1;
	}
	if (d_st->align > 0 && control == 0)
	{
		d_st->c += write(1, "0x", 2);
		tolower1(d_st->str, d_st);
		if ((size_t)d_st->width > ft_strlen(d_st->str))
			width(d_st->width, ft_strlen(d_st->str) + 2, d_st);
		
	}
	else if (d_st->align == 0 && control == 0)
	{
		if ((size_t)d_st->width > ft_strlen(d_st->str))
			width(d_st->width, ft_strlen(d_st->str) + 2, d_st);
		d_st->c += write(1, "0x", 2);
		tolower1(d_st->str, d_st);
	}
}

void precision_unsigned(int precision, int len, p_lista *d_st)
{
	while (precision > len)
	{
		d_st->c += ft_putchar_fd('0');
		len++;
	}
}
