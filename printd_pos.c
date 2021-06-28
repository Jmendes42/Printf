/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmendes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 15:03:20 by jmendes           #+#    #+#             */
/*   Updated: 2021/06/27 18:56:16 by jmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	width_precision(t_lista *s_st, int d, int len)
{
	s_st->width = s_st->width + 1 - s_st->precision;
	if (s_st->align == 1)
	{
		s_st->width -= 1;
		precision(s_st->precision, len, s_st, 0);
		ft_putnbr_fd(d);
		s_st->align++;
		width(s_st->width, 0, s_st);
	}
	else
	{
		s_st->width--;
		width(s_st->width, 0, s_st);
		precision(s_st->precision, len, s_st, 0);
	}
}

static void	zero_pre(t_lista *s_st, int d, int len)
{
	if (s_st->precision < len)
		s_st->precision = len;
	else
	{
		if (d < 0)
		{
			s_st->precision++;
			s_st->c--;
		}
	}
	if (s_st->align == 0)
	{
		width(s_st->zero, s_st->precision, s_st);
		precision(s_st->precision, len, s_st, 0);
	}
	else
	{
		precision(s_st->precision, len, s_st, 0);
		ft_putnbr_fd(d);
		width(s_st->zero, s_st->precision, s_st);
		s_st->align++;
	}
}

static void	width1(t_lista *s_st, int d, int len)
{
	if (s_st->precision > len && s_st->width > s_st->precision)
		width_precision(s_st, d, len);
	else
	{
		if (s_st->align > 0)
		{
			ft_putnbr_fd(d);
			s_st->align++;
		}
		width(s_st->width, len, s_st);
	}
}

void	printd_pos(t_lista *s_st, int d, int num, int len)
{
	while (num > 0)
	{
		num = num / 10;
		len++;
	}
	s_st->c += len;
	if ((s_st->precision >= 0 && s_st->zero > s_st->precision)
		|| (s_st->zero > 0 && s_st->align == 1))
		zero_pre(s_st, d, len);
	else if (s_st->precision > len && s_st->precision >= s_st->width)
		precision(s_st->precision, len, s_st, 0);
	else if (s_st->width > len && s_st->width > s_st->precision)
		width1(s_st, d, len);
	else if (s_st->zero > len && s_st->align == 0 && s_st->precision < 0)
		precision(s_st->zero, len, s_st, 0);
	else if (s_st->zero > s_st->precision)
	{
		if (s_st->precision < -1)
			s_st->precision *= -1;
		precision(s_st->zero, len, s_st, 0);
	}
	 if (s_st->align < 2)
		ft_putnbr_fd(d);
}
