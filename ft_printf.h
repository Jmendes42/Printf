/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmendes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 17:06:01 by jmendes           #+#    #+#             */
/*   Updated: 2021/07/29 05:18:26 by jmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>

typedef struct s_st
{
	unsigned int	c;
	int				align;
	int				width;
	int				precision;
	int				zero;
	char			*str;
	int				type;
	int				p;
	int				backPrint;
}	t_lista;

void	width(int dst, int x, t_lista *d_st);
void	precision(int dst, int index, t_lista *d_st, int control);
void	precision_unsigned(int precision, int len, t_lista *d_st);
void	tolower1(char *s, t_lista *d_st);
int		ft_printf(const char *fmt, ...);
int		ft_putchar_fd(char c);
void	pre_printd(t_lista *d_st, int d);
void	printd_neg(t_lista *d_st, int d, int num, int index);
void	printd_pos(t_lista *d_st, int d, int num, int index);
void	ft_putnbr_fd(int n);
int		ft_putstr_fd(char *s);
size_t	ft_strlen(const char *s);
int		flags(const char *fmt, int index, t_lista *d_st, va_list vars);
void	printc(t_lista *d_st, char c);
void	prints(t_lista *d_st, char *c);
void	printp(t_lista *d_st, unsigned long long n);
char	*convert(unsigned long long n, int base);
void	printx(t_lista *d_st, unsigned long long i, int base, int lower);
void	printx0(t_lista *d_st, int len);
void	printx1(t_lista *d_st, int len);
void	printxx(t_lista *d_st, unsigned long long i);
void	printu(t_lista *d_st, unsigned int d, int base, int lower);
char	*ft_strdup(const char *s);
void	precision_char(int index, char *s, t_lista *d_st);
void	width_precision_neg(t_lista *d_st, int d, int len);
void	width_precision_u(t_lista *d_st, int len);
#endif
