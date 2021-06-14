/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmendes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 00:45:45 by jmendes           #+#    #+#             */
/*   Updated: 2021/06/10 11:17:57 by jmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	counter(unsigned long long n, int base)
{
	int index;

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
	unsigned long long	nr;
	int			index;
	index = counter(n, base);
	d_st->str = (char *)malloc(sizeof(char) * (index + 1));
	d_st->str[index--] = '\0';
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
	d_st->p += 1;
	convert(n, 16, d_st);
	if (d_st->align > 0)
	{
		d_st->c += write(1, "0x", 2);
		tolower1(d_st->str, d_st);
		if ((size_t)d_st->width > ft_strlen(d_st->str))
			width(d_st->width, ft_strlen(d_st->str) + 2, d_st);
		
	}
	else
	{
		if ((size_t)d_st->width > ft_strlen(d_st->str))
			width(d_st->width, ft_strlen(d_st->str) + 2, d_st);
		d_st->c += write(1, "0x", 2);
		tolower1(d_st->str, d_st);
	}
	free (d_st->str);
}

void precision_unsigned(int precision, int len, p_lista *d_st)
{
	while (precision > len)
	{
		d_st->c += ft_putchar_fd('0');
		len++;
	}
}

/*void	printx(p_lista *d_st, unsigned long long i)
{
	int len;

	if (d_st->precision == 0)
		return ;
	convert(i, 16, d_st);
//	ft_putstr_fd(d_st->str);
	len = ft_strlen(d_st->str);
//	ft_putnbr_fd(len);
	if (d_st->align == 0)
	{
		if (d_st->precision > len)
			precision_unsigned(d_st->precision, len - 1, d_st);
		if (d_st->precision >= d_st->width)
			return ;
		if (d_st->width > len)
			width(d_st->width, len, d_st);
		tolower1(d_st->str);
	}
	else
	{
//	ft_putnbr_fd(len);
		tolower1(d_st->str);
		if (d_st->precision > len)
		{
			precision_unsigned(d_st->precision, len, d_st);
			len++;
		}
		if (d_st->precision >= d_st->width)
			return ;
		if (d_st->width > len)
			width(d_st->width, len, d_st);
	}
}*/
