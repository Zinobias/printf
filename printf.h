/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printf.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/20 18:06:26 by zgargasc       #+#    #+#                */
/*   Updated: 2020/01/16 17:19:30 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>
# include <unistd.h>

typedef union	u_int
{
	long long			ll;
	unsigned long long	llu;
	int					i;
	unsigned int		u;
}				t_int;

typedef enum	e_flags
{
	HASH = 1 << 0,
	MIN = 1 << 1,
	PLUS = 1 << 2,
	SPACE = 1 << 3,
	ZERO = 1 << 4,
}				t_flags;

typedef	struct	s_res
{
	int			digits;
	char		buff[23];
	char		buff2[2];
}				t_res;

typedef	struct	s_format
{
	int				width;
	int				precision;
	size_t			char_printed;
	int				length;
	unsigned int	flag_stock;
	size_t			char_read;
}				t_format;

int				ft_atoi(const char *str);
size_t			get_width(const char *f_str, t_format **format, va_list args);
size_t			get_precision(const char *f_str, t_format **format,
				va_list args);
void			buf_handler(char const *txt, size_t len, t_format **format);
size_t			conv_c(va_list args, t_format **format);
void			padding(t_format **format, long long len, int mod);
size_t			conv_s(va_list args, t_format **format);
size_t			conv_i(va_list args, t_format **format);
t_res			ft_itoa(unsigned long long i, int base);
size_t			get_length(const char *f_str, t_format **format);
void			pad_i(t_res res, t_format **format, int sign, char *buff);
size_t			conv_u(va_list args, t_format **format);
size_t			conv_p(va_list args, t_format **format);
t_res			ft_itoa_hex(unsigned long long i, int base, char upper);
size_t			conv_hex_upper(va_list args, t_format **format);
size_t			conv_hex_lower(va_list args, t_format **format);
size_t			conv_n(va_list args, t_format **format);
size_t			get_flags(const char *f_str, t_format **format);
size_t			conv(const char *f_str, t_format **format, va_list args);
size_t			makeformat(const char *f_str, va_list args, t_format **format);
void			ft_read_format(t_format **format,\
				va_list args, const char *f_str);
size_t			conv_perc(va_list args, t_format **f);
#endif
