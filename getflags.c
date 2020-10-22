/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   getflags.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/13 19:01:17 by zgargasc       #+#    #+#                */
/*   Updated: 2020/01/16 17:19:49 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

size_t			get_flags(const char *f_str, t_format **format)
{
	size_t					i;
	static const	t_flags	flag_table[128] =\
	{['#'] = HASH,\
	['-'] = MIN,\
	['+'] = PLUS,\
	['0'] = ZERO,\
	[' '] = SPACE};

	i = 0;
	(*format)->flag_stock = 0;
	while (flag_table[(int)f_str[i]] != 0)
	{
		(*format)->flag_stock |= flag_table[(int)f_str[i]];
		i++;
	}
	return (i);
}

size_t			get_width(const char *f_str, t_format **format, va_list args)
{
	size_t					i;
	char					width[12];

	i = 0;
	if (f_str[i] == '*')
	{
		(*format)->width = va_arg(args, int);
		i = 1;
		if ((*format)->width < 0)
		{
			(*format)->width = (*format)->width * -1;
			(*format)->flag_stock |= MIN;
		}
	}
	else
	{
		while (f_str[i] >= '0' && f_str[i] <= '9')
		{
			width[i] = f_str[i];
			i++;
			width[i] = '\0';
		}
		(*format)->width = ft_atoi(width);
	}
	return (i);
}

size_t			get_length(const char *f_str, t_format **format)
{
	size_t					i;
	static const char		length_table[128] =\
	{['l'] = 1,\
	['h'] = 2};

	i = 0;
	while (length_table[(int)f_str[i]] != 0)
	{
		if (f_str[i] == 'h')
			(*format)->length = 2;
		i++;
	}
	if (i > 0 && (*format)->length != 2)
		(*format)->length = 1;
	return (i);
}

size_t			get_precision(const char *f_str, \
t_format **format, va_list args)
{
	size_t					i;
	char					precision[12];

	i = 0;
	if (!(f_str[i] >= '0' && f_str[i] <= '9') && f_str[i] != '*')
		(*format)->precision = 0;
	else if (f_str[i] == '*')
	{
		(*format)->precision = va_arg(args, int);
		if ((*format)->precision < 0)
			(*format)->precision = -1;
		i++;
	}
	else
	{
		while (f_str[i] >= '0' && f_str[i] <= '9')
		{
			precision[i] = f_str[i];
			i++;
			precision[i] = '\0';
		}
		(*format)->precision = ft_atoi(precision);
	}
	return (i);
}
