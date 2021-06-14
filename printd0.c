/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printd0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmendes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 15:03:02 by jmendes           #+#    #+#             */
/*   Updated: 2021/06/11 17:54:04 by jmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	width(int dst, int x, p_lista *d_st)
{
	while (dst > x)
	{
		d_st->c = d_st->c + ft_putchar_fd(' ');
		dst--;
	}
}

static void	zero_pre(p_lista *d_st, int d)
{
	if (d_st->precision > 0)
	{
		if (d_st->align == 0)
		{
			width (d_st->width, d_st->precision, d_st);
			precision(d_st->precision, &d, 0, d_st);
		}
		else
		{
			precision(d_st->precision, &d, 0, d_st);
			width (d_st->width, d_st->precision, d_st);
		}
	}
}

static void	zero_pre1(p_lista *d_st, int d)
{
	if (d_st->align == 0)
	{
		precision(d_st->zero, &d, 1, d_st);
		width(d_st->width, 1, d_st);
		d_st->c += ft_putchar_fd('0');
	}
	else
	{
		d_st->c += ft_putchar_fd('0');
		width(d_st->width, 1, d_st);
	}
}

static void	zero(p_lista *d_st, int d)
{		
	if (d_st->precision > 0 && d_st->zero > d_st->precision)
	{
		width (d_st->zero, d_st->precision, d_st);
		precision(d_st->precision, &d, 0, d_st);
	}
	else if (d_st->precision == 0 && d_st->width > 0)
		width (d_st->width, d_st->precision, d_st);
	else if (d_st->precision == 0 && d_st->zero != 0)
		width(d_st->zero, 0, d_st);
	else if (d_st->precision == 0)
		 return ;
	else if (d_st->precision > 0)
		zero_pre(d_st, d);
	else
		zero_pre1(d_st, d);
}

void	printd(p_lista *d_st, int d)
{
	int	index;
	int	num;

	index = 0;
	num = d;
	if (d < 0)
	{
		if (num == -2147483648)
			num = 2147483647;
		else
			num *= -1;
		printd0(d_st, d, num, index + 1);
	}
	else if (d == 0)
		zero(d_st, d);
	else
		printd1(d_st, d, num, index);
}
