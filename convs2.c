/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convs2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/13 19:02:34 by zgargasc       #+#    #+#                */
/*   Updated: 2020/01/13 20:08:46 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

size_t			conv_hex_lower(va_list args, t_format **format)
{
	unsigned int			x;
	t_res					res;
	char					buff[2];

	x = va_arg(args, unsigned int);
	if ((*format)->flag_stock & HASH)
	{
		buff[0] = '0';
		buff[1] = 'x';
		(*format)->width -= 2;
	}
	if (x == 0)
	{
		res.buff[0] = '0';
		res.digits = (*format)->precision == 0 ? 0 : 1;
		pad_i(res, format, 1, buff);
	}
	else
		pad_i(ft_itoa_hex(x, 16, 'a'), format, 1, buff);
	return (1);
}

size_t			conv_hex_upper(va_list args, t_format **format)
{
	unsigned int			x;
	t_res					res;
	char					buff[2];

	x = va_arg(args, unsigned int);
	if ((*format)->flag_stock & HASH)
	{
		buff[0] = '0';
		buff[1] = 'X';
		(*format)->width -= 2;
	}
	if (x == 0)
	{
		res.buff[0] = '0';
		res.digits = (*format)->precision == 0 ? 0 : 1;
		pad_i(res, format, 1, buff);
	}
	else
		pad_i(ft_itoa_hex(x, 16, 'A'), format, 1, buff);
	return (1);
}

size_t			conv_i(va_list args, t_format **format)
{
	int						sign;
	t_int					type;
	t_res					res;

	sign = 1;
	if ((*format)->length == 1)
		type.ll = va_arg(args, long long);
	else
		type.ll = va_arg(args, int);
	if (type.ll < 0)
	{
		sign = -1;
		type.llu = type.ll * -1;
	}
	if (type.llu == 0)
	{
		res.digits = (*format)->precision == 0 ? 0 : 1;
		res.buff[0] = '0';
		pad_i(res, format, sign, NULL);
	}
	else
		pad_i(ft_itoa(type.llu, 10), format, sign, NULL);
	return (1);
}

size_t			conv_u(va_list args, t_format **format)
{
	int						sign;
	t_int					type;
	t_res					res;

	sign = 1;
	if ((*format)->length == 1)
		type.llu = va_arg(args, unsigned long long);
	else
		type.llu = va_arg(args, unsigned int);
	if (type.llu == 0)
	{
		res.digits = (*format)->precision == 0 ? 0 : 1;
		res.buff[0] = '0';
		pad_i(res, format, sign, NULL);
	}
	else
		pad_i(ft_itoa(type.llu, 10), format, sign, NULL);
	return (1);
}
