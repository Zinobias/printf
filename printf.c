/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printf.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/20 18:06:24 by zgargasc       #+#    #+#                */
/*   Updated: 2020/01/29 21:23:03 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

size_t	conv(const char *f_str, t_format **format, va_list args)
{
	size_t				i;
	static	size_t		(*f_array[128])(va_list, t_format **) =\
	{['c'] = &conv_c,\
	['s'] = &conv_s,\
	['p'] = &conv_p,\
	['d'] = &conv_i,\
	['i'] = &conv_i,\
	['u'] = &conv_u,\
	['n'] = &conv_n,\
	['%'] = &conv_perc,\
	['x'] = &conv_hex_lower,\
	['X'] = &conv_hex_upper};

	i = 0;
	if (f_str[i] == 'c' || f_str[i] == 's' || f_str[i] == 'p' || \
	f_str[i] == 'd' || f_str[i] == 'i' || f_str[i] == 'u' || f_str[i] == 'n'\
	|| f_str[i] == 'x' || f_str[i] == 'X' || f_str[i] == '%')
	{
		(*f_array[(int)f_str[i]])(args, format);
		i++;
	}
	return (i);
}

size_t	makeformat(const char *f_str, va_list args, t_format **format)
{
	size_t	i;

	i = 0;
	(*format)->width = 0;
	(*format)->length = 0;
	(*format)->precision = -1;
	i += get_flags(f_str, format);
	if ((f_str[i] >= '0' && f_str[i] <= '9') || f_str[i] == '*')
		i += get_width(f_str + i, format, args);
	if (f_str[i] == '.')
		i += get_precision(f_str + i + 1, format, args) + 1;
	i += get_length(f_str + i, format);
	i += conv(f_str + i, format, args);
	return (i);
}

void	buf_handler(char const *txt, size_t len, t_format **format)
{
	static char		buff[1000];
	static size_t	current = 0;

	while (len > 0)
	{
		buff[current] = *txt;
		len--;
		current++;
		(*format)->char_read++;
		(txt)++;
		if (current == sizeof(buff))
		{
			(*format)->char_printed += write(1, buff, sizeof(buff));
			current = 0;
		}
	}
	if (txt == NULL)
	{
		(*format)->char_printed += write(1, buff, current);
		current = 0;
	}
}

void	ft_read_format(t_format **format, va_list args, const char *f_str)
{
	size_t		count;
	size_t		index;
	size_t		pos;

	count = 0;
	index = 0;
	pos = 0;
	while (f_str[index])
	{
		if (f_str[index] == '%')
		{
			buf_handler(f_str + pos, index - pos, format);
			index++;
			index += makeformat(f_str + index, args, format);
			pos = index;
			count = 0;
		}
		else
		{
			count++;
			index++;
		}
	}
	if (count > 0)
		buf_handler(f_str + pos, count, format);
}

int		ft_printf(const char *f_str, ...)
{
	va_list					args;
	t_format				*format;
	size_t					i;

	format = (t_format*)malloc(sizeof(t_format));
	if (!format)
		return (-1);
	format->char_printed = 0;
	format->char_read = 0;
	va_start(args, f_str);
	ft_read_format(&format, args, f_str);
	va_end(args);
	buf_handler(NULL, 0, &format);
	i = format->char_printed;
	free(format);
	return (i);
}
