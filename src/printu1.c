/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printu1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmendes <jmendes@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 15:03:20 by jmendes           #+#    #+#             */
/*   Updated: 2022/09/29 02:32:29 by jmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

void	width_precision_u(t_lista *s_st, int len)
{
	s_st->width = s_st->width + 1 - s_st->precision;
	if (s_st->align == 1)
	{
		s_st->width -= 1;
		precision_unsigned(s_st->precision, len, s_st);
		s_st->c += ft_putstr_fd(s_st->str);
		s_st->align++;
		width(s_st->width, 0, s_st);
	}
	else
	{
		s_st->width--;
		width(s_st->width, 0, s_st);
		precision_unsigned(s_st->precision, len, s_st);
	}
}
