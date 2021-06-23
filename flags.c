/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmendes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 18:35:37 by jmendes           #+#    #+#             */
/*   Updated: 2021/06/23 17:22:16 by jmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
static void ast1(p_lista *d_st, int d)
{
	d_st->zero = d;
	if (d < 0)
	{
		d_st->zero *= -1;
		d_st->align = 1;
	}

}
static void ast0(p_lista *d_st, int d)
{
	d_st->precision = d;
}
static void ast(p_lista *d_st, int d)
{
	d_st->width = d;
	if (d_st->width < 0)
	{
		d_st->width *= -1;
		d_st->align = 1;
	}
}

void flags(p_lista *d_st, const char **fmt, va_list vars)
{
	if ((char)**fmt == '-')
	{
		d_st->align = 1;
		(*fmt)++;
	}
	if ((char)**fmt == '0')
	{
		(*fmt)++;
		while ((char)**fmt >= '0' && (char)**fmt <= '9')
		{
			d_st->zero = (d_st->zero * 10) + (char)**fmt - '0';
			(*fmt)++;
		}

		if (**fmt == '*')
		{
			ast1(d_st, va_arg(vars, int));
			(*fmt)++;
		}
	}

	if ((char)**fmt == '-')
	{
		d_st->align = 1;
		(*fmt)++;
	}
	if ((char)**fmt == '*')
	{
		ast(d_st, va_arg(vars, int));
		(*fmt)++;
	}
	if ((char)**fmt >= '1' && (char)**fmt <= '9')
	{
		while ((char)**fmt >= '0' && (char)**fmt <= '9')
		{
			d_st->width = (d_st->width * 10) + (char)**fmt - '0';
			(*fmt)++;
		}
	}

	if ((char)**fmt == '.')
	{
		d_st->precision++;
		(*fmt)++;
//		ft_putchar_fd('X');
		while ((char)**fmt >= '0' && (char)**fmt <= '9')
		{
			d_st->precision = (d_st->precision * 10) + (char)**fmt - '0';
			(*fmt)++;
		}
	}
	if ((char)**fmt == '*')
	{
		ast0(d_st, va_arg(vars, int));
		(*fmt)++;
	}

}
