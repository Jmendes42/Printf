/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmendes <jmendes@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 21:31:56 by jmendes           #+#    #+#             */
/*   Updated: 2022/09/29 02:32:20 by jmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static void	printsAlign1(char *s, t_lista *s_st)
{
	if (s_st->zero > 0)
	{
		s_st->c += ft_putstr_fd(s);
		if ((size_t)s_st->zero > ft_strlen(s))
			width(s_st->zero, ft_strlen(s), s_st);
	}
	else
	{
		precision_char(s_st->precision, s, s_st);
		width(s_st->width, s_st->precision, s_st);
	}
}

static void	printsAlign0(char *s, t_lista *s_st)
{
	if (s_st->zero > 0)
	{
		if ((size_t)s_st->zero > ft_strlen(s))
			precision(s_st->zero, ft_strlen(s), s_st, 0);
		s_st->c += ft_putstr_fd(s);
	}
	else
		width(s_st->width, s_st->precision, s_st);
	precision_char(s_st->precision, s, s_st);
}

static void	printsWidth(char *s, t_lista *s_st)
{
	if (s_st->align > 0)
	{
		s_st->c += ft_putstr_fd(s);
		width(s_st->width, ft_strlen(s), s_st);
	}
	else
	{
		width(s_st->width, ft_strlen(s), s_st);
		s_st->c += ft_putstr_fd(s);
	}
}

void	prints(t_lista *s_st, char *s)
{
	if (!s)
		s = "(null)";
	if ((size_t)s_st->precision > ft_strlen(s))
		s_st->precision = -1;
	if ((s_st->precision >= 0 && s_st->width > s_st->precision)
		|| s_st->zero > 0)
	{
		if (s_st->zero > s_st->width)
			s_st->width = s_st->zero - ft_strlen(s);
		if (s_st->align == 1)
			printsAlign1(s, s_st);
		else
			printsAlign0(s, s_st);
	}
	else if (s_st->precision >= 0 && s_st->precision >= s_st->width)
		precision_char(s_st->precision, s, s_st);
	else if (s_st->width > 0 && s_st->precision == -1)
		printsWidth(s, s_st);
	else
		s_st->c += ft_putstr_fd(s);
}
