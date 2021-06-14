/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printd1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmendes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 15:03:02 by jmendes           #+#    #+#             */
/*   Updated: 2021/06/14 15:45:10 by jmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	width_precision(p_lista *d_st, int *d, int index)
{
	if (*d != -1 && d_st->align == 1)
	{
		d_st->precision++;
	}
	d_st->width = d_st->width - d_st->precision;
	if (d_st->align == 1)
	{
		if (d_st->precision == index)
		{
			index--;
			d_st->width--;
		}
		if (d_st->width == 1)
		{
			precision(d_st->precision, d, index -1, d_st);
			d_st->width = 0;
		}
		else
			precision(d_st->precision, d, index, d_st);
		ft_putnbr_fd(*d);
		d_st->align++;
		width(d_st->width, 0, d_st);
	}
	else
	{
		d_st->width--;
		width(d_st->width, 0, d_st);
		precision(d_st->precision, d, index - 1, d_st);
	}
}

static void	width1(p_lista *d_st, int *d, int index)
{
	if (d_st->precision >= index && d_st->width > d_st->precision)
	{
		width_precision(d_st, d, index);
	}
	else
	{	
		if (d_st->align > 0)
		{
			ft_putnbr_fd(*d);
			d_st->align++;
		}
		if (d_st->precision == index)
		{
			width(d_st->width, index + 1, d_st);
			precision(d_st->precision, d, index - 1, d_st);
		}
		else
			width(d_st->width, index, d_st);
	}
}

static void	pre_zero(p_lista *d_st, int *d, int index)
{
	if (d_st->precision < index)
		d_st->precision = index;
	else
		d_st->precision++;
	if (d_st->align == 0)
	{
		width(d_st->zero, d_st->precision, d_st);
		precision(d_st->precision, d, index, d_st);
	}
	else
	{
		precision(d_st->precision, d, index, d_st);
		ft_putnbr_fd(*d);
		width(d_st->zero, d_st->precision, d_st);
		d_st->align++;
	}
}

void	printd0(p_lista *d_st, int d, int num, int index)
{
	while (num > 0)
	{
		num = num / 10;
		index++;
	}
	d_st->c += index;
	if (d_st->zero > index && d_st->align == 1 && d_st->precision == -1)
	{
		ft_putnbr_fd(d);
		width(d_st->zero, index, d_st);
		d_st->align++;
	}
	else if (d_st->precision >= 0 && d_st->zero > d_st->precision)
	{
		pre_zero(d_st, &d, index);
	}
	else if (d_st->precision > index && d_st->precision >= d_st->width)
		precision(d_st->precision, &d, index - 1, d_st);
	else if (d_st->width > index && d_st->width > d_st->precision)
	{
		width1(d_st, &d, index);
	}
	else if (d_st->zero > index && d_st->align == 0 && d_st->precision == -1)
		precision(d_st->zero, &d, index, d_st);
	if (d_st->align != 2)
		ft_putnbr_fd(d);
}
