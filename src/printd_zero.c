/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printd_zero.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmendes <jmendes@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 15:41:29 by jmendes           #+#    #+#             */
/*   Updated: 2022/09/29 02:32:03 by jmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static void	zero_pre(t_lista *s_st)
{
	if (s_st->precision > 0)
	{
		if (s_st->align == 0)
		{
			width (s_st->width, s_st->precision, s_st);
			precision(s_st->precision, 0, s_st, 0);
		}
		else
		{
			precision(s_st->precision, 0, s_st, 0);
			width (s_st->width, s_st->precision, s_st);
		}
	}
}

static void	zero_pre1(t_lista *s_st)
{
	if (s_st->zero > 0 && s_st->precision < 0 && s_st->align == 0)
	{
		precision(s_st->zero, 0, s_st, 0);
		return ;
	}
	if (s_st->zero == s_st->precision)
	{
		s_st->c += ft_putchar_fd('0');
		width(s_st->precision, 1, s_st);
		return ;
	}
	if (s_st->align == 0)
	{
		precision(s_st->zero, 1, s_st, 0);
		width(s_st->width, 1, s_st);
		s_st->c += ft_putchar_fd('0');
	}
	else
	{
		if (s_st->zero > 0 && s_st->width == 0)
			s_st->width = s_st->zero;
		s_st->c += ft_putchar_fd('0');
		width(s_st->width, 1, s_st);
	}
}

static void	precision_zero(t_lista *s_st)
{
	if (s_st->align == 0)
	{
		width (s_st->zero, s_st->precision, s_st);
		precision(s_st->precision, 0, s_st, 0);
	}
	else
	{
		precision(s_st->precision, 0, s_st, 0);
		width (s_st->zero, s_st->precision, s_st);
	}
}

static void	printd_zero(t_lista *s_st)
{		
	if (s_st->precision > 0 && s_st->zero > s_st->precision)
		precision_zero(s_st);
	else if (s_st->zero > 0 && s_st->align == 1 && s_st->precision == -1)
	{
		s_st->c++;
		ft_putnbr_fd(0);
		width(s_st->zero, 1, s_st);
	}
	else if (s_st->precision == 0 && s_st->width > 0)
		width (s_st->width, s_st->precision, s_st);
	else if (s_st->precision == 0 && s_st->zero != 0)
		width(s_st->zero, 0, s_st);
	else if (s_st->precision == 0)
		 return ;
	else if (s_st->precision > 0)
		zero_pre(s_st);
	else
		zero_pre1(s_st);
}

void	pre_printd(t_lista *s_st, int d)
{
	int	index;
	int	num;

	index = 0;
	num = d;
	if (s_st->align > 1)
		s_st->align = 1;
	if (d < 0)
	{
		if (num == -2147483648)
			num = 2147483647;
		else
			num *= -1;
		printd_neg(s_st, d, num, index + 1);
	}
	else if (d == 0)
		printd_zero(s_st);
	else
		printd_pos(s_st, d, num, index);
}
