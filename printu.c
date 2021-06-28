/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printu.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmendes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 15:03:20 by jmendes           #+#    #+#             */
/*   Updated: 2021/06/27 18:58:50 by jmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	zero_pre(t_lista *s_st, int len)
{
	if (s_st->precision < len)
		s_st->precision = len;
	if (s_st->align == 0)
	{
		width(s_st->zero, s_st->precision, s_st);
		precision_unsigned(s_st->precision, len, s_st);
	}
	else
	{
		precision_unsigned(s_st->precision, len, s_st);
		s_st->c += ft_putstr_fd(s_st->str);
		width(s_st->zero, s_st->precision, s_st);
		s_st->align++;
	}
}

static void	width1(t_lista *s_st, int len)
{
	if (s_st->precision > len && s_st->width > s_st->precision)
		width_precision_u(s_st, len);
	else
	{
		if (s_st->align == 1)
		{
			s_st->c += ft_putstr_fd(s_st->str);
			s_st->align++;
		}
		width(s_st->width, len, s_st);
	}
}

void	zero_u(unsigned int d, t_lista *s_st, int len)
{
	if (s_st->zero > s_st->precision && s_st->precision == 0)
	{
		if (s_st->align == 0)
			width(s_st->zero, len, s_st);
		else
		{
			if (d == 0)
				len--;
			s_st->c += ft_putstr_fd(s_st->str);
			width(s_st->zero, len, s_st);
			s_st->align++;
		}
	}
	else
		zero_pre(s_st, len);
}

static int	precisionZero(int len, int control, t_lista *s_st)
{
	free (s_st->str);
	s_st->str[0] = '\0';
	if (s_st->zero > 0)
	{
		width(s_st->zero, 0, s_st);
		return (control + 1);
	}
	else if (s_st->width > s_st->precision && s_st->precision == 0)
		width(s_st->width + 1, len, s_st);
	else if (s_st->width > s_st->precision)
	{
		width(s_st->width, len, s_st);
		if (s_st->width > 2)
			len++;
	}
	return (control + 1);
}

void	printu(t_lista *s_st, unsigned int d, int base, int lower)
{
	int		len;
	int		control;

	control = 0;
	s_st->str = convert(d, base);
	if (lower == 1)
		tolower1(s_st->str, s_st);
	len = ft_strlen(s_st->str);
	if (s_st->str[0] == '0' && s_st->str[1] == '2')
		s_st->str[0] = '\0';
	if (d == 0 && s_st->precision == 0 )
		control = precisionZero(len, control, s_st);
	if (s_st->precision >= 0 && s_st->zero > s_st->precision
		&& s_st->zero > len && control == 0)
		zero_u(d, s_st, len);
	else if (s_st->precision > len && s_st->precision >= s_st->width)
		precision_unsigned(s_st->precision, len, s_st);
	else if (s_st->width > len && s_st->width > s_st->precision && control == 0)
		width1(s_st, len);
	else if (s_st->zero > len && s_st->align == 0 && s_st->precision == -1)
		precision_unsigned(s_st->zero, len, s_st);
	if (s_st->align < 2)
		 s_st->c += ft_putstr_fd(s_st->str);
	if (s_st->str[0] != '\0')
		free (s_st->str);
}
