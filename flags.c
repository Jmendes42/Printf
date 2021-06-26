/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmendes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 18:35:37 by jmendes           #+#    #+#             */
/*   Updated: 2021/06/26 20:58:32 by jmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	astZero(p_lista *d_st, int d)
{
	d_st->zero = d;
	if (d < 0)
	{
		d_st->zero *= -1;
		d_st->align = 1;
	}
}

static int	flagZero(const char *fmt, int index, p_lista *d_st, va_list vars)
{
	while (fmt[index] == '0' || fmt[index] == '-')
	{
		while (fmt[index] == '-')
		{
			d_st->align = 1;
			index++;
		}
		if (fmt[index] != '0')
			return (index);
		while (fmt[index] == '0')
			index++;
		while (fmt[index] >= '0' && fmt[index] <= '9')
		{
			d_st->zero = (d_st->zero * 10) + fmt[index] - '0';
			index++;
		}
		if (fmt[index] == '*')
		{
			astZero(d_st, va_arg(vars, int));
			index++;
		}
	}
	return (index);
}

static int	flagWidth(const char *fmt, int index, p_lista *d_st, va_list vars)
{
	if (fmt[index] == '-')
	{
		d_st->align = 1;
		index++;
	}
	if (fmt[index] == '*')
	{
		d_st->width = va_arg(vars, int);
		if (d_st->width < 0)
		{
			d_st->width *= -1;
			d_st->align = 1;
		}
		index++;
	}
	if (fmt[index] >= '1' && fmt[index] <= '9')
	{
		while (fmt[index] >= '0' && fmt[index] <= '9')
		{
			d_st->width = (d_st->width * 10) + fmt[index] - '0';
			index++;
		}
	}
	return (index);
}

static int	flagPrecision(const char *fmt, int index, p_lista *d_st,
		va_list vars)
{
	if (fmt[index] == '.')
	{
		d_st->precision = 0;
		index++;
		while (fmt[index] >= '0' && fmt[index] <= '9')
		{
			d_st->precision = (d_st->precision * 10) + fmt[index] - '0';
			index++;
		}
	}
	if (fmt[index] == '*')
	{
		d_st->precision = va_arg(vars, int);
		index++;
	}
	return (index);
}

int	flags(const char *fmt, int index, p_lista *d_st, va_list vars)
{
	if (fmt[index] == '0' || fmt[index] == '-')
	{
		index = flagZero(fmt, index, d_st, vars);
	}
	if ((fmt[index] >= '0' && fmt[index] <= '9') || fmt[index] == '-'
		|| fmt[index] == '*')
	{
		index = flagWidth(fmt, index, d_st, vars);
	}
	if (fmt[index] == '.')
		index = flagPrecision(fmt, index, d_st, vars);
	return (index);
}
