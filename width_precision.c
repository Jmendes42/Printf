/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width_precision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmendes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 15:58:12 by jmendes           #+#    #+#             */
/*   Updated: 2021/06/16 16:45:31 by jmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void    precision(int dst, int len, p_lista *d_st)
{
	if (d_st->precision == len)
		return ;
	while (dst > len)
	{
		d_st->c += ft_putchar_fd('0');
		len++;
	}
}

void    width(int dst, int x, p_lista *d_st)
{
	while (dst > x)
	{
		d_st->c = d_st->c + ft_putchar_fd(' ');
		dst--;
	}
}
