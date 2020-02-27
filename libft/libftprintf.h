/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libftprintf.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/05 11:14:05 by bmans         #+#    #+#                 */
/*   Updated: 2019/12/05 11:14:05 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H
# ifndef U_LL
#  define U_LL unsigned long long
# endif
# ifndef CONV_LIST
#  define CONV_LIST "cspdiuxX%"
# endif
# include <stdarg.h>
# include <stdlib.h>
# include "libft.h"

typedef struct	s_print
{
	va_list		ap;
	char		*form;
	U_INT		len;
	int			width;
	int			prec;
	char		pad;
	char		left;
	char		conv;
}				t_print;

int				ft_printf(const char *format, ...);
void			ft_print_flags(t_print *print);
char			*ft_print_resize(char *str, t_print *print);
char			*ft_itoa_prec(int n, int prec);
char			*ft_itoa_base_prec(U_LL n, char *basedigits, int prec);
void			ft_print_char(t_print *print);
void			ft_print_string(t_print *print);
void			ft_print_ptr(t_print *print);
void			ft_print_int(t_print *print);
void			ft_print_uint(t_print *print);

#endif
