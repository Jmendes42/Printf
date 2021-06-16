/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmendes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 14:30:06 by jmendes           #+#    #+#             */
/*   Updated: 2021/06/16 17:17:43 by jmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"
#include <limits.h>

void	backPrint(const char *fmt, p_lista *d_st)
{
	d_st->backPrint += 1;
	fmt--;
	while (*fmt != '%')
	{
		d_st->c += write(1, &*fmt, 1);
		fmt--;
	}
}

static void	type(p_lista *d_st, va_list vars, const char **fmt)
{
	if (**fmt == 'u')
		printu(d_st, va_arg(vars, unsigned int));
	else if (**fmt == 'X')
		printxx(d_st, va_arg(vars, unsigned long long));
	else if (**fmt == 'x')
		printx(d_st, va_arg(vars, unsigned long long));
	else if (**fmt == 'p')
		printp(d_st, va_arg(vars, unsigned long long));
	else if (**fmt == 's')
		prints(d_st, va_arg(vars, char *));
	else if (**fmt == 'c')
		printc(d_st, va_arg(vars, int));
	else if (**fmt == 'd' || **fmt == 'i')
		pre_printd(d_st, va_arg(vars, int));
	else if (**fmt == '%')
		printc(d_st, '%');
	else
		d_st->type += 1;
	(*fmt)++;	
}

static void init_struct(p_lista *d_st)
{
	d_st->align = 0;
	d_st->width = 0;
	d_st->precision = -1;
	d_st->zero = 0;
	d_st->str = NULL;
	d_st->type = 0;
	d_st->p = 0;
	d_st->backPrint = 0;
}

int ft_printf(const char *fmt, ...)
{
	va_list vars;
	int index;
	struct d_st d_st;

	d_st.c = 0;
	index = 0;
	init_struct(&d_st);
	va_start(vars, fmt);

	while (*fmt != '\0')
	{
		if(*fmt == '%')
		{
			fmt++;
			if (*fmt == '\0')
				break;
			flags(&d_st, &fmt, vars);
			type(&d_st, vars, &fmt);
			if (d_st.type != 0)
			{
				backPrint(fmt, &d_st);
				break;
			}
		}
		if (*fmt == '\0')
			break;
		if(*fmt != '%')
		{
			d_st.c += ft_putchar_fd(*fmt);
			fmt++;
		}
		init_struct(&d_st);
	}
	va_end(vars);
	return (d_st.c);
}

/*int	main(void)
{
	int e;
	e = ft_printf("%9.2d\n", UINT_MAX);
//	e = ft_printf("%11.10i\n", UINT_MAX);
//		ft_printf("-00216 i  \n");
//	  ft_printf("0000%%\n");
	  ft_printf("Numero de chars impressos = %d\n", e);
	return (0);
}*/
//print1.c width_precision -> verificar incrementos


//VERIFICAR:
