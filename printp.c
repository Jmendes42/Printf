/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmendes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 18:24:55 by jmendes           #+#    #+#             */
/*   Updated: 2021/06/27 18:57:55 by jmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	alignControl(t_lista *s_st)
{
	s_st->c += write(1, "0x", 2);
	tolower1(s_st->str, s_st);
	if ((size_t)s_st->width > ft_strlen(s_st->str))
		width(s_st->width, ft_strlen(s_st->str) + 2, s_st);
}

void	printp(t_lista *s_st, unsigned long long n)
{
	int	control;

	control = 0;
	s_st->p += 1;
	s_st->str = convert(n, 16);
	if (!n && s_st->precision == 0)
		s_st->str[0] = '\0';
	if (s_st->precision > 0 && s_st->width < s_st->precision)
	{
		s_st->c += write(1, "0x", 2);
		precision(s_st->precision, ft_strlen(s_st->str), s_st, 0);
		tolower1(s_st->str, s_st);
		control += 1;
	}
	if (s_st->align > 0 && control == 0)
		alignControl(s_st);
	else if (s_st->align == 0 && control == 0)
	{
		if ((size_t)s_st->width > ft_strlen(s_st->str))
			width(s_st->width, ft_strlen(s_st->str) + 2, s_st);
		s_st->c += write(1, "0x", 2);
		tolower1(s_st->str, s_st);
	}
	free(s_st->str);
}
