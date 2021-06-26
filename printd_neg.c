/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printd1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmendes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 15:03:02 by jmendes           #+#    #+#             */
/*   Updated: 2021/06/26 22:01:31 by jmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	width_precision(p_lista *d_st, int d, int len)
{
	if (d != -1 && d_st->align == 1)
		d_st->precision++;
	d_st->width = d_st->width - d_st->precision;
	if (d_st->align == 1)
	{
		if (d_st->precision == len)
		{
			len--;
			d_st->width--;
		}
		if (d_st->width == 1)
		{
			precision(d_st->precision, len - 1, d_st, 1);
			d_st->width = 0;
		}
		else
			precision(d_st->precision, len, d_st, 1);
		ft_putnbr_fd(d * -1);
		d_st->align++;
		width(d_st->width, 0, d_st);
	}
	else
	{
		width(d_st->width - 1, 0, d_st);
		precision(d_st->precision, len - 1, d_st, 1);
		ft_putnbr_fd(d * -1);
		d_st->align = 2;
	}
}

static void	width1(p_lista *d_st, int d, int len)
{
	if (d_st->precision >= len && d_st->width > d_st->precision)
	{
		width_precision(d_st, d, len);
	}
	else
	{	
		if (d_st->align > 0)
		{
			ft_putnbr_fd(d);
			d_st->align = 2;
		}
		if (d_st->precision == len)
		{
			width(d_st->width, len + 1, d_st);
			precision(d_st->precision, len - 1, d_st, 1);
		}
		else
			width(d_st->width, len, d_st);
	}
}

static void	pre_zero(p_lista *d_st, int d, int len)
{
	int	control;

	control = 1;
	if (d_st->precision < len)
		d_st->precision = len;
	else
		d_st->precision++;
	if (d_st->align == 0)
	{
		width(d_st->zero, d_st->precision, d_st);
		if (d != -2147483648)
		{
			d_st->align = 2;
			d *= -1;
		}
		if (d_st->align != 2)
			precision(d_st->precision, len, d_st, 0);
		if (d_st->align == 2)
		{
			precision(d_st->precision, len, d_st, 1);		
			ft_putnbr_fd(d);
		}
	}
	else
	{
		if (d == -2147483648)
			control = 0;
		precision(d_st->precision, len, d_st, control);
		ft_putnbr_fd(d * -1);
		width(d_st->zero, d_st->precision, d_st);
		d_st->align++;
	}
}

void	printd_neg(p_lista *d_st, int d, int num, int len)
{
	while (num > 0)
	{
		num = num / 10;
		len++;
	}
	d_st->c += len;
	if (d_st->zero > len && d_st->align == 1 && d_st->precision == -1)
	{
		ft_putnbr_fd(d);
		width(d_st->zero, len, d_st);
		d_st->align++;
	}
	else if (d_st->precision >= 0 && d_st->zero > d_st->precision)
		pre_zero(d_st, d, len);
	else if (d_st->precision >= len && d_st->precision >= d_st->width)
	{
		precision(d_st->precision, len - 1, d_st, 1);
		d *= -1;
	}
	else if (d_st->width > d_st->precision && d_st->width > len)
		width1(d_st, d, len);
	else if (d_st->zero > len && d_st->align == 0 && d_st->precision < 0)
	{
		precision(d_st->zero, len, d_st, 1);
		d *= -1;
	}
	if (d_st->align != 2)
		ft_putnbr_fd(d);
}
