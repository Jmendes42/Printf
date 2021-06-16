/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printx0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmendes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 15:41:11 by jmendes           #+#    #+#             */
/*   Updated: 2021/06/16 15:37:36 by jmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	printx0(p_lista *d_st, int len)
{
	if (d_st->precision == 0)
	{
		if (d_st->width == 1)
			d_st->c += ft_putchar_fd(' ');
		d_st->str[0] = '\0';
		if (d_st->width > d_st->precision)
		{
			width(d_st->width, len, d_st);
			if (d_st->width > 2)
				len++;
		}
		else if (d_st->align == 0)
			d_st->zero++;
	}
	else if (d_st->precision > 0)
		precision_unsigned(d_st->precision, len, d_st);
	else
		d_st->c += ft_putchar_fd('0');
}
