/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmendes <jmendes@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 14:30:06 by jmendes           #+#    #+#             */
/*   Updated: 2022/09/29 02:31:27 by jmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static int	backPrint(const char *fmt, int index, t_lista *s_st)
{
	int	index_0;

	index_0 = index - 1;
	while (fmt[index] != '%')
		index--;
	while (index < index_0)
	{
		s_st->c += write(1, &fmt[index], 1);
		index++;
	}
	s_st->backPrint += 1;
	return (index);
}

static int	type(char fmt, int index, t_lista *s_st, va_list vars)
{
	if (fmt == 'u')
		printu(s_st, va_arg(vars, unsigned int), 10, 0);
	else if (fmt == 'X')
		printu(s_st, va_arg(vars, unsigned int), 16, 0);
	else if (fmt == 'x')
		printu(s_st, va_arg(vars, unsigned int), 16, 1);
	else if (fmt == 'p')
		printp(s_st, va_arg(vars, unsigned long long));
	else if (fmt == 's')
		prints(s_st, va_arg(vars, char *));
	else if (fmt == 'c')
	{
		printc(s_st, va_arg(vars, int));
	}
	else if (fmt == 'd' || fmt == 'i')
		pre_printd(s_st, va_arg(vars, int));
	else if (fmt == '%')
		printc(s_st, '%');
	else
		s_st->type += 1;
	return (index + 1);
}

static void	init_struct(t_lista *s_st)
{
	s_st->align = 0;
	s_st->width = 0;
	s_st->precision = -1;
	s_st->zero = 0;
	s_st->type = 0;
	s_st->p = 0;
	s_st->backPrint = 0;
}

static int	mainLoop(const char *fmt, int index, t_lista *s_st, va_list vars)
{
	index++;
	if (fmt[index] == '\0')
		return (index);
	index = flags(fmt, index, s_st, vars);
	index = type(fmt[index], index, s_st, vars);
	if (s_st->type != 0)
	{
		index = backPrint(fmt, index, s_st);
		return (index);
	}
	return (index);
}

int	ft_printf(const char *fmt, ...)
{
	va_list		vars;
	int			index;
	struct s_st	s_st;

	s_st.c = 0;
	index = 0;
	init_struct(&s_st);
	va_start(vars, fmt);
	while (fmt)
	{
		if (fmt[index] == '%')
			index = mainLoop(fmt, index, &s_st, vars);
		if (fmt[index] == '\0')
			break ;
		if (fmt[index] != '%')
		{
			s_st.c += ft_putchar_fd(fmt[index]);
			index++;
		}
		init_struct(&s_st);
	}
	va_end(vars);
	return (s_st.c);
}
