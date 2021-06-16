/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmendes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 15:03:20 by jmendes           #+#    #+#             */
/*   Updated: 2021/06/16 20:50:45 by jmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	width_precision(p_lista *d_st, int len)
{
	d_st->width = d_st->width + 1 - d_st->precision;
	if (d_st->align == 1)
	{
		d_st->width -= 1;
		precision_unsigned(d_st->precision, len, d_st);
		d_st->c += ft_putstr_fd(d_st->str);
		d_st->align++;
		width(d_st->width, 0, d_st);
	}
	else
	{
		d_st->width--;
		width(d_st->width, 0, d_st);
		precision_unsigned(d_st->precision, len, d_st);
	}
}

static void	zero_pre(p_lista *d_st, int len)
{
	if (d_st->precision < len)
		d_st->precision = len;
	if (d_st->align == 0)
	{
		width(d_st->zero, d_st->precision, d_st);
		precision_unsigned(d_st->precision, len, d_st);
	}
	else
	{
		precision_unsigned(d_st->precision, len, d_st);
		d_st->c += ft_putstr_fd(d_st->str);
		width(d_st->zero, d_st->precision, d_st);
		d_st->align++;
	}
}

static void	width1(p_lista *d_st, int len)
{
	if (d_st->precision > len && d_st->width > d_st->precision)
		width_precision(d_st, len);
	else
	{
		if (d_st->align == 1)
		{
			d_st->c += ft_putstr_fd(d_st->str);
			d_st->align++;
		}
		width(d_st->width, len, d_st);
	}
}

static void	zero_u(p_lista *d_st, int len)
{
	if (d_st->zero > d_st->precision && d_st->precision == 0)
	{
		if (d_st->align == 0)
			width(d_st->zero, len, d_st);
		else
		{
			d_st->c += ft_putstr_fd(d_st->str);
			width(d_st->zero, len, d_st);
			d_st->align++;
		}
	}
	else
		zero_pre(d_st, len);
}

void	printx1(p_lista *d_st, int len)
{
	if (d_st->precision >= 0 && d_st->zero > d_st->precision
		&& d_st->zero > len)
		{
		zero_u(d_st, len);
		}
	else if (d_st->precision > len && d_st->precision >= d_st->width)
	{
		precision(d_st->precision, len, d_st, 0);
	}
	else if (d_st->width > len && d_st->width > d_st->precision)
		width1(d_st, len);
	else if (d_st->zero > len && d_st->align == 0 && d_st->precision == -1)
		precision_unsigned(d_st->zero, len, d_st);
	if (d_st->align < 2)
		 d_st->c += ft_putstr_fd(d_st->str);
}

void	printx(p_lista *d_st, unsigned long long d, int base, int lower)
{
	int	len;

	convert(d, base, d_st);
	if (lower == 1)
		tolower1(d_st->str, d_st);
	len = ft_strlen(d_st->str);

	if (d == 0)
		printx0(d_st, len);
	else
		printx1(d_st, len);
	free (d_st->str);
}
