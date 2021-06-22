/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmendes <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 17:06:01 by jmendes           #+#    #+#             */
/*   Updated: 2021/06/22 15:59:29 by jmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdio.h> 

	typedef struct d_st
	{
		unsigned int c;
		int align;
		int width;
		int precision;
		int zero;
		char *str;
		int type;
		int p;
		int backPrint;
	} p_lista;



//precision_width
void	width(int dst, int x, p_lista *d_st);
void    precision(int dst, int index, p_lista *d_st, int control);
void    precision_unsigned(int precision, int len, p_lista *d_st);


int		ft_printf(const char *fmt, ...);
int	ft_putchar_fd(char c);
void	pre_printd(p_lista *d_st, int d);
void	printd_neg(p_lista *d_st, int d, int num, int index);
void	printd_pos(p_lista *d_st, int d, int num, int index);
void    ft_putnbr_fd(int n);
int	ft_putstr_fd(char *s);
size_t	ft_strlen(const char *s);
void		flags(p_lista *d_st, const char **fmt, va_list vars);
void	printc(p_lista *d_st, char c);
void	prints(p_lista *d_st, char *c);
void	printp(p_lista *d_st, unsigned long long n);
char       *convert(unsigned long long n, int base, p_lista *d_st);
void    printx(p_lista *d_st, unsigned long long i, int base, int lower);
void    printx0(p_lista *d_st, int len);
void    printx1(p_lista *d_st, int len);
void    printxx(p_lista *d_st, unsigned long long i);
void    printu(p_lista *d_st, unsigned int d, int base, int lower);
char    *ft_strdup(const char *s);
void	tolower1(char *s, p_lista *d_st);
/*void		ft_print_c(p_lista *d_st, char c);
void		ft_print_s(p_lista *d_st, char *s);
int	ft_type(const char *fmt, int index, p_lista *d_st,va_list vars);
char	*ft_convert(unsigned long long n, int base);
void	ft_print_p(p_lista *d_st, unsigned long long p);
void	ft_print_x(p_lista *d_st, unsigned long long x);
void	ft_print_x_up(p_lista *d_st, unsigned long long x_up);
void	ft_print_u(p_lista *d_st, unsigned long long u);

char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int 	ft_isdigit(int c);
void    *ft_memset(void *s, int c, size_t n);
char		*ft_itoa(int n);
char	*ft_strjoin(char const *s1, char const *s2);*/

#endif
