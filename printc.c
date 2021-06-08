/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmendes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 16:12:38 by jmendes           #+#    #+#             */
/*   Updated: 2021/06/05 22:44:50 by jmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void precision_char(int index, char *s, p_lista *d_st)
{
	while (index-- > 0)
	{
		d_st->c += ft_putchar_fd(*s);
		s++;
	}
}

void printc(p_lista *d_st, char c)
{
	if ( c == '%' && d_st->zero > 0)
	{
		if (d_st->align == 1)
		{
			d_st->c += ft_putchar_fd(c);
			width(d_st->zero, 1, d_st);
			d_st->align++;
		}
		else
			precision_unsigned(d_st->zero, 1, d_st);
	}
	if (d_st->width < 0)
	{
		d_st->align = 1;
		d_st->width *= -1;
	}
	if (d_st->width > 0)
	{
		if (d_st->align > 0)
		{
			d_st->c += ft_putchar_fd(c);
			width(d_st->width, 1, d_st);
		}
		else
		{
			width(d_st->width, 1, d_st);
			d_st->c += ft_putchar_fd(c);
		}
	}
	else if (d_st->align < 2)
		d_st->c += ft_putchar_fd(c);
}


void prints(p_lista *d_st, char *s)
{
	if (!s)
		s = "(null)";	
	if (d_st->width < 0)
	{
		d_st->align = 1; 
		d_st->width *= -1; 
	}
	if (d_st->precision <= -1)
		d_st->precision = ft_strlen(s);
	if ((size_t)d_st->precision > ft_strlen(s))
		d_st->precision = -1;
	if (d_st->precision >= 0 && d_st->width > d_st->precision)
	{
		if (d_st->align == 1)
		{
			precision_char(d_st->precision, s, d_st);
			width(d_st->width, d_st->precision, d_st);
		}
		else
		{
			width(d_st->width, d_st->precision, d_st);
			precision_char(d_st->precision, s, d_st);
		}
	}
	else if (d_st->precision >= 0 && d_st->precision >= d_st->width)
		precision_char(d_st->precision, s, d_st);
	else if (d_st->width > 0 && d_st->precision == -1)
	{
		if (d_st->align > 0)
		{
			d_st->c += ft_putstr_fd(s);
			width(d_st->width, ft_strlen(s), d_st);
		}
		else
		{
			width(d_st->width, ft_strlen(s), d_st);
			d_st->c += ft_putstr_fd(s);
		}
	}
	else
		d_st->c += ft_putstr_fd(s);
}

void printxx(p_lista *d_st, unsigned long long i)
{
	char *str;
	int len;

	convert(i, 16, d_st);
	d_st->c += len = ft_strlen(str);
	if (d_st->align == 0)
	{
		if (d_st->width > len)
			width(d_st->width, len, d_st);
		 write(1, str, sizeof(str));
	}
	else
	{
		write(1, str, sizeof(str));
		if (d_st->width > len)
			width(d_st->width, len, d_st);
	}
}
