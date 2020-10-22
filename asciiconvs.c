/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   asciiconvs.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/13 19:01:38 by zgargasc       #+#    #+#                */
/*   Updated: 2020/01/13 19:05:53 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static	long	ft_max(long result, long s)
{
	if (LONG_MAX / result <= 10 && s == 1)
		return (-1);
	else if (LONG_MAX / result <= 10 && s == -1)
		return (0);
	return (1);
}

int				ft_atoi(const char *str)
{
	long					i;
	long					s;
	long					result;

	i = 0;
	s = 1;
	result = 0;
	while (str[i])
	{
		result = result * 10 + str[i] - '0';
		if (result != 0)
			if (ft_max(result, s) < 1)
				return (ft_max(result, s));
		i++;
	}
	return ((int)(result * s));
}

t_res			ft_itoa(unsigned long long i, int base)
{
	int						current;
	char					digits[21];
	t_res					res;

	current = 0;
	if (i == 0)
	{
		res.buff[0] = '0';
		res.digits = 1;
		return (res);
	}
	while (i > 0)
	{
		digits[current] = (i % base + '0');
		i = i / base;
		current++;
	}
	res.digits = 0;
	while (current - 1 >= 0)
	{
		res.buff[res.digits] = digits[current - 1];
		current--;
		res.digits++;
	}
	return (res);
}

t_res			ft_itoa_hex(unsigned long long i, int base, char upper)
{
	int						current;
	char					digits[21];
	t_res					res;

	current = 0;
	while (i > 0)
	{
		digits[current] = i % base > 9 ? (i % base - 10) \
		+ upper : (i % base) + '0';
		i = i / base;
		current++;
	}
	base = 0;
	current--;
	while (current >= 0)
	{
		res.buff[base] = digits[current];
		current--;
		base++;
	}
	res.digits = base;
	return (res);
}
