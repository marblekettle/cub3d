/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libftprintf.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <bmans@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/25 13:36:49 by bmans         #+#    #+#                 */
/*   Updated: 2020/06/25 13:54:24 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H
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
	u_int32_t	len;
	int			width;
	int			prec;
	char		pad;
	char		left;
	char		conv;
	int			out;
}				t_print;

int				ft_printf(const char *format, ...);
int				ft_printf_fd(int fd, const char *format, ...);
void			ft_print_flags(t_print *print);
char			*ft_print_resize(char *str, t_print *print);
char			*ft_itoa_prec(int n, int prec);
char			*ft_itoa_base_prec(u_int64_t n, char *basedigits, int prec);
void			ft_print_char(t_print *print);
void			ft_print_string(t_print *print);
void			ft_print_ptr(t_print *print);
void			ft_print_int(t_print *print);
void			ft_print_uint(t_print *print);

#endif
