/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmendes <jmendes@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 16:12:38 by jmendes           #+#    #+#             */
/*   Updated: 2022/09/29 02:31:31 by jmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

void	printcWidth(char c, t_lista *s_st)
{
	if (s_st->align > 0)
	{
		s_st->c += ft_putchar_fd(c);
		width(s_st->width, 1, s_st);
	}
	else
	{
		width(s_st->width, 1, s_st);
		s_st->c += ft_putchar_fd(c);
	}
}

void	printc(t_lista *s_st, char c)
{
	if (c == '%' && s_st->zero > 0)
	{
		if (s_st->align == 1)
		{
			s_st->c += ft_putchar_fd(c);
			width(s_st->zero, 1, s_st);
			s_st->align++;
		}
		else
			precision_unsigned(s_st->zero, 1, s_st);
	}
	if (s_st->width < 0)
	{
		s_st->align = 1;
		s_st->width *= -1;
	}
	if (s_st->width > 0)
		printcWidth(c, s_st);
	else if (s_st->align < 2)
		s_st->c += ft_putchar_fd(c);
}
