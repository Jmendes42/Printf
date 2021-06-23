/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printd_zero.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmendes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 15:41:29 by jmendes           #+#    #+#             */
/*   Updated: 2021/06/23 17:21:58 by jmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	zero_pre(p_lista *d_st)
{
	if (d_st->precision > 0)
	{
		if (d_st->align == 0)
		{
			width (d_st->width, d_st->precision, d_st);
			precision(d_st->precision, 0, d_st, 0);
		}
		else
		{
			precision(d_st->precision, 0, d_st, 0);
			width (d_st->width, d_st->precision, d_st);
		}
	}
}

static void	zero_pre1(p_lista *d_st)
{
	if (d_st->align == 0)
	{
		precision(d_st->zero, 1, d_st, 0);
		width(d_st->width, 1, d_st);
		d_st->c += ft_putchar_fd('0');
	}
	else
	{
		d_st->c += ft_putchar_fd('0');
		width(d_st->width, 1, d_st);
	}
}

static void	printd_zero(p_lista *d_st)
{		
	if (d_st->precision > 0 && d_st->zero > d_st->precision)
	{
		width (d_st->zero, d_st->precision, d_st);
		precision(d_st->precision, 0, d_st, 0);
	}
	else if (d_st->zero > 0 && d_st->align == 1 && d_st->precision == -1)
	{
		d_st->c++;
		ft_putnbr_fd(0);
		width(d_st->zero, 1, d_st);
	}
	else if (d_st->precision == 0 && d_st->width > 0)
	{
		width (d_st->width, d_st->precision, d_st);
	}
	else if (d_st->precision == 0 && d_st->zero != 0)
	{
		width(d_st->zero, 0, d_st);
	}
	else if (d_st->precision == 0)
	{
		 return ;
	}
	else if (d_st->precision > 0)
	{
		zero_pre(d_st);
	}
	else
	{
		zero_pre1(d_st);
	}
}

void	pre_printd(p_lista *d_st, int d)
{
	int	index;
	int	num;

	index = 0;
	num = d;
	if (d_st->align > 1)
		d_st->align = 1;
	if (d < 0)
	{
		if (num == -2147483648)
			num = 2147483647;
		else
			num *= -1;
		printd_neg(d_st, d, num, index + 1);
	}
	else if (d == 0)
		printd_zero(d_st);
	else
		printd_pos(d_st, d, num, index);
}
