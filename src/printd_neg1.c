/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printd_neg1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmendes <jmendes@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 15:45:56 by jmendes           #+#    #+#             */
/*   Updated: 2022/09/29 02:31:57 by jmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static void	w_p_n(int d, int len, t_lista *s_st)
{
	if (s_st->precision == len)
	{
		len--;
		s_st->width--;
	}
	if (s_st->width == 1)
	{
		precision(s_st->precision, len - 1, s_st, 1);
		s_st->width = 0;
	}
	else
		precision(s_st->precision, len, s_st, 1);
	ft_putnbr_fd(d * -1);
	s_st->align++;
	width(s_st->width, 0, s_st);
}

void	width_precision_neg(t_lista *s_st, int d, int len)
{
	if (d != -1 && s_st->align == 1)
		s_st->precision++;
	s_st->width = s_st->width - s_st->precision;
	if (s_st->align == 1)
		w_p_n(d, len, s_st);
	else
	{
		width(s_st->width - 1, 0, s_st);
		precision(s_st->precision, len - 1, s_st, 1);
		ft_putnbr_fd(d * -1);
		s_st->align = 2;
	}
}
