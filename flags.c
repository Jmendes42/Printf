/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmendes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 18:35:37 by jmendes           #+#    #+#             */
/*   Updated: 2021/06/27 18:52:08 by jmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	astZero(t_lista *s_st, int d)
{
	s_st->zero = d;
	if (d < 0)
	{
		s_st->zero *= -1;
		s_st->align = 1;
	}
}

static int	flagZero(const char *fmt, int index, t_lista *s_st, va_list vars)
{
	while (fmt[index] == '0' || fmt[index] == '-')
	{
		while (fmt[index] == '-')
		{
			s_st->align = 1;
			index++;
		}
		if (fmt[index] != '0')
			return (index);
		while (fmt[index] == '0')
			index++;
		while (fmt[index] >= '0' && fmt[index] <= '9')
		{
			s_st->zero = (s_st->zero * 10) + fmt[index] - '0';
			index++;
		}
		if (fmt[index] == '*')
		{
			astZero(s_st, va_arg(vars, int));
			index++;
		}
	}
	return (index);
}

static int	flagWidth(const char *fmt, int index, t_lista *s_st, va_list vars)
{
	if (fmt[index] == '-')
	{
		s_st->align = 1;
		index++;
	}
	if (fmt[index] == '*')
	{
		s_st->width = va_arg(vars, int);
		if (s_st->width < 0)
		{
			s_st->width *= -1;
			s_st->align = 1;
		}
		index++;
	}
	if (fmt[index] >= '1' && fmt[index] <= '9')
	{
		while (fmt[index] >= '0' && fmt[index] <= '9')
		{
			s_st->width = (s_st->width * 10) + fmt[index] - '0';
			index++;
		}
	}
	return (index);
}

static int	flagPrecision(const char *fmt, int index, t_lista *s_st,
		va_list vars)
{
	if (fmt[index] == '.')
	{
		s_st->precision = 0;
		index++;
		while (fmt[index] >= '0' && fmt[index] <= '9')
		{
			s_st->precision = (s_st->precision * 10) + fmt[index] - '0';
			index++;
		}
	}
	if (fmt[index] == '*')
	{
		s_st->precision = va_arg(vars, int);
		index++;
	}
	return (index);
}

int	flags(const char *fmt, int index, t_lista *s_st, va_list vars)
{
	if (fmt[index] == '0' || fmt[index] == '-')
	{
		index = flagZero(fmt, index, s_st, vars);
	}
	if ((fmt[index] >= '0' && fmt[index] <= '9') || fmt[index] == '-'
		|| fmt[index] == '*')
	{
		index = flagWidth(fmt, index, s_st, vars);
	}
	if (fmt[index] == '.')
		index = flagPrecision(fmt, index, s_st, vars);
	return (index);
}
