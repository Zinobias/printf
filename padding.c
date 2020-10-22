/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   padding.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/13 19:03:41 by zgargasc       #+#    #+#                */
/*   Updated: 2020/01/15 18:32:05 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void			pad_i(t_res res, t_format **f, int sign, char *buff)
{
	char					c;
	int						i;
	int						temp;

	i = (sign == -1 || (*f)->flag_stock & PLUS) ? 1 : 0;
	c = sign == -1 ? '-' : '+';
	c = (*f)->flag_stock & SPACE && sign != -1 ? ' ' : c;
	temp = (*f)->precision > res.digits ? (*f)->precision : res.digits;
	(*f)->width -= (*f)->precision >= 0 ? temp + i : res.digits + i;
	if ((*f)->precision >= 0 || (*f)->flag_stock & MIN)
		(*f)->flag_stock &= ~(ZERO);
	if ((*f)->flag_stock & ZERO && (sign == -1 || \
	(*f)->flag_stock & PLUS || c == ' '))
		buf_handler(&c, 1, f);
	if (!((*f)->flag_stock & MIN))
		padding(f, (*f)->width, 0);
	if ((sign == -1 || c == ' ' || (*f)->flag_stock & PLUS) \
	&& !((*f)->flag_stock & ZERO))
		buf_handler(&c, 1, f);
	padding(f, (*f)->precision - res.digits, 1);
	if ((*f)->flag_stock & HASH)
		buf_handler(buff, 2, f);
	buf_handler(res.buff, res.digits, f);
	if (((*f)->flag_stock & MIN))
		padding(f, (*f)->width, 0);
}

void			padding(t_format **f, long long len, int mod)
{
	char					buff[50];
	size_t					current;
	char					c;

	if (mod == 1)
		c = '0';
	else if (mod == 0)
		c = (*f)->flag_stock & ZERO && (*f)->precision <= 0 ? '0' : ' ';
	current = 0;
	while (len > 0)
	{
		if (current == sizeof(buff))
		{
			buf_handler(buff, sizeof(buff), f);
			current = 0;
		}
		else
		{
			buff[current] = c;
			current++;
			len--;
		}
	}
	if (current > 0)
		buf_handler(buff, current, f);
}
