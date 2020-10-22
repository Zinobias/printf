/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convs.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/13 19:02:01 by zgargasc       #+#    #+#                */
/*   Updated: 2020/01/15 18:36:55 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

size_t			conv_c(va_list args, t_format **format)
{
	char					buff;

	buff = (char)va_arg(args, int);
	if (!((*format)->flag_stock & MIN) && (*format)->width > 0)
		padding(format, (*format)->width - 1, 0);
	buf_handler(&buff, 1, format);
	if ((*format)->flag_stock & MIN && (*format)->width > 0)
		padding(format, (*format)->width - 1, 0);
	return (1);
}

size_t			conv_s(va_list args, t_format **f)
{
	char					*str;
	size_t					strlen;

	strlen = 0;
	str = (va_arg(args, char*));
	if (!str)
	{
		strlen = (*f)->precision < 6 && \
		(*f)->precision != -1 ? (*f)->precision : 6;
	}
	else
		while (str[strlen])
			strlen++;
	if ((*f)->precision != -1 && str && strlen > (size_t)(*f)->precision)
		strlen = (*f)->precision;
	(*f)->width -= strlen;
	if (!((*f)->flag_stock & MIN) && (*f)->width > 0)
		padding(f, (*f)->width, 0);
	if (str)
		buf_handler(str, strlen, f);
	else
		buf_handler("(null)", strlen, f);
	if (((*f)->flag_stock & MIN) && (*f)->width > 0)
		padding(f, (*f)->width, 0);
	return (1);
}

size_t			conv_p(va_list args, t_format **format)
{
	void					*p;
	t_res					res;
	static	char			buff[2] = {'0', 'x'};

	p = va_arg(args, void*);
	if (!p && (*format)->precision != 0)
	{
		res.buff[0] = '0';
		res.digits = 1;
	}
	else
		res = ft_itoa_hex((unsigned long long)p, 16, 'a');
	(*format)->width -= 2;
	(*format)->flag_stock |= HASH;
	pad_i(res, format, 1, buff);
	return (1);
}

size_t			conv_n(va_list args, t_format **format)
{
	int						*i;

	i = va_arg(args, int*);
	*i = (*format)->char_read;
	return (1);
}

size_t			conv_perc(va_list args, t_format **f)
{
	(*f)->width -= 1;
	(void)args;
	if ((*f)->flag_stock & MIN)
		(*f)->flag_stock &= ~(ZERO);
	if (!((*f)->flag_stock & MIN))
		padding(f, (*f)->width, 0);
	buf_handler("%", 1, f);
	if ((*f)->flag_stock & MIN)
		padding(f, (*f)->width, 0);
	return (1);
}
