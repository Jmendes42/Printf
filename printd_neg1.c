/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printd_neg1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmendes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 15:45:56 by jmendes           #+#    #+#             */
/*   Updated: 2021/06/27 16:42:42 by jmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	w_p_n(int d, int len, p_lista *d_st)
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

void	width_precision_neg(p_lista *d_st, int d, int len)
{
	if (d != -1 && d_st->align == 1)
		d_st->precision++;
	d_st->width = d_st->width - d_st->precision;
	if (d_st->align == 1)
		w_p_n(d, len, d_st);
	else
	{
		width(d_st->width - 1, 0, d_st);
		precision(d_st->precision, len - 1, d_st, 1);
		ft_putnbr_fd(d * -1);
		d_st->align = 2;
	}
}
