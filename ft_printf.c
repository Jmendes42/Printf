/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmendes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 14:30:06 by jmendes           #+#    #+#             */
/*   Updated: 2021/06/27 17:24:35 by jmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"
#include <limits.h>

static int	backPrint(const char *fmt, int index, p_lista *d_st)
{
	int	index_0;

	index_0 = index - 1;
	while (fmt[index] != '%')
		index--;
	while (index < index_0)
	{
		d_st->c += write(1, &fmt[index], 1);
		index++;
	}
	d_st->backPrint += 1;
	return (index);
}

static int	type(char fmt, int index, p_lista *d_st, va_list vars)
{
	if (fmt == 'u')
		printu(d_st, va_arg(vars, unsigned int), 10, 0);
	else if (fmt == 'X')
		printu(d_st, va_arg(vars, unsigned int), 16, 0);
	else if (fmt == 'x')
		printu(d_st, va_arg(vars, unsigned int), 16, 1);
	else if (fmt == 'p')
		printp(d_st, va_arg(vars, unsigned long long));
	else if (fmt == 's')
		prints(d_st, va_arg(vars, char *));
	else if (fmt == 'c')
	{
		printc(d_st, va_arg(vars, int));
	}
	else if (fmt == 'd' || fmt == 'i')
		pre_printd(d_st, va_arg(vars, int));
	else if (fmt == '%')
		printc(d_st, '%');
	else
		d_st->type += 1;
	return (index + 1);
}

static void	init_struct(p_lista *d_st)
{
	d_st->align = 0;
	d_st->width = 0;
	d_st->precision = -1;
	d_st->zero = 0;
	d_st->type = 0;
	d_st->p = 0;
	d_st->backPrint = 0;
}

static int	mainLoop(const char *fmt, int index, p_lista *d_st, va_list vars)
{
	index++;
	if (fmt[index] == '\0')
		return (index);
	index = flags(fmt, index, d_st, vars);
	index = type(fmt[index], index, d_st, vars);
	if (d_st->type != 0)
	{
		index = backPrint(fmt, index, d_st);
		return (index);
	}
	return (index);
}

int	ft_printf(const char *fmt, ...)
{
	va_list		vars;
	int			index;
	struct d_st	d_st;

	d_st.c = 0;
	index = 0;
	init_struct(&d_st);
	va_start(vars, fmt);
	while (fmt)
	{
		if (fmt[index] == '%')
			index = mainLoop(fmt, index, &d_st, vars);
		if (fmt[index] == '\0')
			break ;
		if (fmt[index] != '%')
		{
			d_st.c += ft_putchar_fd(fmt[index]);
			index++;
		}
		init_struct(&d_st);
	}
	va_end(vars);
	return (d_st.c);
}

/*int	main(void)
{
	int e;
	e = ft_printf  ("%0*.*u", 2, 0, 0);
//	e = ft_printf("%09s\n", "hi low");
//		ft_printf("-00216 i  \n");
//	  ft_printf("0000%%\n");
//	  ft_printf("Numero de chars impressos = %d\n", e);
	return (0);
}*/
//print1.c width_precision -> verificar incrementos
//VERIFICAR: flags-> recursiva
