/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmendes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 21:31:56 by jmendes           #+#    #+#             */
/*   Updated: 2021/06/26 21:58:30 by jmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	printsAlign1(char *s, p_lista *d_st)
{
	if (d_st->zero > 0)
	{
		d_st->c += ft_putstr_fd(s);
		if ((size_t)d_st->zero > ft_strlen(s))
			width(d_st->zero, ft_strlen(s), d_st);
	}
	else
	{
		precision_char(d_st->precision, s, d_st);
		width(d_st->width, d_st->precision, d_st);
	}
}

static void	printsAlign0(char *s, p_lista *d_st)
{
	if (d_st->zero > 0)
	{
		if ((size_t)d_st->zero > ft_strlen(s))
			precision(d_st->zero, ft_strlen(s), d_st, 0);
		d_st->c += ft_putstr_fd(s);
	}
	else
		width(d_st->width, d_st->precision, d_st);
	precision_char(d_st->precision, s, d_st);
}

static void	printsWidth(char *s, p_lista *d_st)
{
	if (d_st->align > 0)
	{
		d_st->c += ft_putstr_fd(s);
		width(d_st->width, ft_strlen(s), d_st);
	}
	else
	{
		width(d_st->width, ft_strlen(s), d_st);
		d_st->c += ft_putstr_fd(s);
	}
}

void	prints(p_lista *d_st, char *s)
{
	if (!s)
		s = "(null)";
	if ((size_t)d_st->precision > ft_strlen(s))
		d_st->precision = -1;
	if ((d_st->precision >= 0 && d_st->width > d_st->precision)
		|| d_st->zero > 0)
	{
		if (d_st->zero > d_st->width)
			d_st->width = d_st->zero - ft_strlen(s);
		if (d_st->align == 1)
			printsAlign1(s, d_st);
		else
			printsAlign0(s, d_st);
	}
	else if (d_st->precision >= 0 && d_st->precision >= d_st->width)
		precision_char(d_st->precision, s, d_st);
	else if (d_st->width > 0 && d_st->precision == -1)
		printsWidth(s, d_st);
	else
		d_st->c += ft_putstr_fd(s);
}
