/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmendes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 15:03:20 by jmendes           #+#    #+#             */
/*   Updated: 2021/06/24 14:43:14 by jmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	width_precision(p_lista *d_st, int d, int len)
{
	d_st->width = d_st->width + 1 - d_st->precision;
	if (d_st->align == 1)
	{
		d_st->width -= 1;
		precision(d_st->precision, len, d_st, 0);
		ft_putnbr_fd(d);
		d_st->align++;
		width(d_st->width, 0, d_st);
	}
	else
	{
		d_st->width--;
		width(d_st->width, 0, d_st);
		precision(d_st->precision, len, d_st, 0);
	}
}

static void	zero_pre(p_lista *d_st, int d, int len)
{
	if (d_st->precision < len)
		d_st->precision = len;
	else
	{
		if (d < 0)
		{
			d_st->precision++;
			d_st->c--;
		}
	}
	if (d_st->align == 0)
	{
		width(d_st->zero, d_st->precision, d_st);
		precision(d_st->precision, len, d_st, 0);
	}
	else
	{
		precision(d_st->precision, len, d_st, 0);
		ft_putnbr_fd(d);
		width(d_st->zero, d_st->precision, d_st);
		d_st->align++;
	}
}

static void	width1(p_lista *d_st, int d, int len)
{
	if (d_st->precision > len && d_st->width > d_st->precision)
		width_precision(d_st, d, len);
	else
	{
		if (d_st->align > 0)
		{
			ft_putnbr_fd(d);
			d_st->align++;
		}
		width(d_st->width, len, d_st);
	}
}

void	printd_pos(p_lista *d_st, int d, int num, int len)
{
	while (num > 0)
	{
		num = num / 10;
		len++;
	}
	d_st->c += len;
	if ((d_st->precision >= 0 && d_st->zero > d_st->precision) || d_st->zero > 0&& d_st->align == 1)
	{
		zero_pre(d_st, d, len);
	}
	else if (d_st->precision > len && d_st->precision >= d_st->width)
	{
		precision(d_st->precision, len, d_st, 0);
	}
	else if (d_st->width > len && d_st->width > d_st->precision)
	{
		width1(d_st, d, len);
	}
	else if (d_st->zero > len && d_st->align == 0 && d_st->precision == -1)
	{
		precision(d_st->zero, len, d_st, 0);
	}
	else if (d_st->zero > d_st->precision)
	{
		if (d_st->precision < -1)
			d_st->precision *= -1;
		precision(d_st->zero, len, d_st, 0);
	}
	 if (d_st->align < 2)
	 {
		ft_putnbr_fd(d);
	 }
}
