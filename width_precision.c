/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width_precision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmendes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 15:58:12 by jmendes           #+#    #+#             */
/*   Updated: 2021/06/26 21:30:54 by jmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void    precision(int zero, int len, p_lista *d_st, int control)
{
	if (control == 1)
		ft_putchar_fd('-');
	if (d_st->precision == len)
		return ;
	while (zero > len++)
		d_st->c += ft_putchar_fd('0');
}

void    width(int space, int len, p_lista *d_st)
{
	while (space-- > len)
		d_st->c = d_st->c + ft_putchar_fd(' ');
}

void precision_char(int index, char *s, p_lista *d_st)
{
	while (index-- > 0)
	{
		d_st->c += ft_putchar_fd(*s);
		s++;
	}
}
