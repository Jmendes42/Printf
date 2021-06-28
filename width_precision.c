/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width_precision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmendes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 15:58:12 by jmendes           #+#    #+#             */
/*   Updated: 2021/06/27 18:59:59 by jmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	precision(int zero, int len, t_lista *s_st, int control)
{
	if (control == 1)
		ft_putchar_fd('-');
	if (s_st->precision == len)
		return ;
	while (zero > len++)
		s_st->c += ft_putchar_fd('0');
}

void	width(int space, int len, t_lista *s_st)
{
	while (space-- > len)
		s_st->c = s_st->c + ft_putchar_fd(' ');
}

void	precision_char(int index, char *s, t_lista *s_st)
{
	while (index-- > 0)
	{
		s_st->c += ft_putchar_fd(*s);
		s++;
	}
}
