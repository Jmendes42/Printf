/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmendes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 16:12:38 by jmendes           #+#    #+#             */
/*   Updated: 2021/06/26 21:41:40 by jmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	printcWidth(char c, p_lista *d_st)
{
	if (d_st->align > 0)
	{
		d_st->c += ft_putchar_fd(c);
		width(d_st->width, 1, d_st);
	}
	else
	{
		width(d_st->width, 1, d_st);
		d_st->c += ft_putchar_fd(c);
	}
}

void	printc(p_lista *d_st, char c)
{
	if (c == '%' && d_st->zero > 0)
	{
		if (d_st->align == 1)
		{
			d_st->c += ft_putchar_fd(c);
			width(d_st->zero, 1, d_st);
			d_st->align++;
		}
		else
			precision_unsigned(d_st->zero, 1, d_st);
	}
	if (d_st->width < 0)
	{
		d_st->align = 1;
		d_st->width *= -1;
	}
	if (d_st->width > 0)
		printcWidth(c, d_st);
	else if (d_st->align < 2)
		d_st->c += ft_putchar_fd(c);
}
