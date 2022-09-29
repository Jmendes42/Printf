/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printd_neg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmendes <jmendes@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 16:17:45 by jmendes           #+#    #+#             */
/*   Updated: 2022/09/29 02:31:35 by jmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static void	width1(t_lista *s_st, int d, int len)
{
	if (s_st->precision >= len && s_st->width > s_st->precision)
	{
		width_precision_neg(s_st, d, len);
	}
	else
	{	
		if (s_st->align > 0)
		{
			ft_putnbr_fd(d);
			s_st->align = 2;
		}
		if (s_st->precision == len)
		{
			width(s_st->width, len + 1, s_st);
			precision(s_st->precision, len - 1, s_st, 1);
		}
		else
			width(s_st->width, len, s_st);
	}
}

static void	pre_zero1(int d, int len, t_lista *s_st)
{
	width(s_st->zero, s_st->precision, s_st);
	if (d != -2147483648)
	{
		s_st->align = 2;
		d *= -1;
	}
	if (s_st->align != 2)
		precision(s_st->precision, len, s_st, 0);
	if (s_st->align == 2)
	{
		precision(s_st->precision, len, s_st, 1);
		ft_putnbr_fd(d);
	}
}

static void	pre_zero(t_lista *s_st, int d, int len)
{
	int	control;

	control = 1;
	if (s_st->precision < len)
		s_st->precision = len;
	else
		s_st->precision++;
	if (s_st->align == 0)
		pre_zero1(d, len, s_st);
	else
	{
		if (d == -2147483648)
			control = 0;
		precision(s_st->precision, len, s_st, control);
		ft_putnbr_fd(d * -1);
		width(s_st->zero, s_st->precision, s_st);
		s_st->align++;
	}
}

static void	print_neg1(int d, int len, t_lista *s_st)
{
	if (s_st->precision >= 0 && s_st->zero > s_st->precision)
		pre_zero(s_st, d, len);
	else if (s_st->precision >= len && s_st->precision >= s_st->width)
	{
		precision(s_st->precision, len - 1, s_st, 1);
		d *= -1;
	}
	else if (s_st->width > s_st->precision && s_st->width > len)
		width1(s_st, d, len);
	else if (s_st->zero > len && s_st->align == 0 && s_st->precision < 0)
	{
		precision(s_st->zero, len, s_st, 1);
		d *= -1;
	}
	if (s_st->align != 2)
		ft_putnbr_fd(d);
}

void	printd_neg(t_lista *s_st, int d, int num, int len)
{
	while (num > 0)
	{
		num = num / 10;
		len++;
	}
	s_st->c += len;
	if (s_st->zero > len && s_st->align == 1 && s_st->precision == -1)
	{
		ft_putnbr_fd(d);
		width(s_st->zero, len, s_st);
		s_st->align++;
	}
	else
		print_neg1(d, len, s_st);
}
