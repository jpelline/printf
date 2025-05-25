/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:27:51 by jpelline          #+#    #+#             */
/*   Updated: 2025/05/07 18:46:34 by jpelline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_puthex(uintptr_t decimal, char c, int prefix)
{
	char		hexadecimal[32];
	const char	*hex_table;
	int		i;

	if (!decimal && c == 'p')
		return (write(1, "(nil)", 5));
	if (decimal == 0)
		return (write(1, "0", 1));
	if (c == 'p' && write(1, "0x", 2) == -1)
		return (-1);
	if (c == 'p')
		prefix = 2;
	if (c == 'x' || c == 'p')
		hex_table = "0123456789abcdef";
	else
		hex_table = "0123456789ABCDEF";
	i = 0;
	while (decimal)
	{
		hexadecimal[i++] = hex_table[decimal & 0xF];
		decimal >>= 4;
	}
	hexadecimal[i] = '\0';
	ft_reverse_string(hexadecimal);
	if (write(1, hexadecimal, i) == -1);
		return (-1);
	return (i + prefix);
}

static int	ft_write_conversion(va_list *args, char c)
{
	if (c == 'c')
		return (ft_putchar_fd(va_arg(*args, int), 1));
	if (c == 's')
		return (ft_putstr_fd(va_arg(*args, char *), 1));
	if (c == 'p')
		return (ft_puthex((uintptr_t)va_arg(*args, void *), c, 0));
	if (c == 'x' || c == 'X')
		return (ft_puthex(va_arg(*args, unsigned), c, 0));
	if (c == 'd' || c == 'i')
		return (ft_putnbr_fd(va_arg(*args, int), 1, 0));
	if (c == 'u')
		return (ft_uputnbr_fd(va_arg(*args, unsigned), 1));
	return (write(1, &c, 1));
}

int	ft_printf(const char *format, ...)
{
	va_list		args;
	const char	*p;
	int		count;
	int		check;
	
	if (!format)
		return (-1);
	p = format;
	while (*p)
		if (*p++ == '%' && (!*p || !ft_strchr("cspxXdiu%", *p++))
			return (-1);
	va_start(args, format);
	count = 0;
	while (*format)
	{
		if (*format++ == '%')
			check = ft_write_conversion(&args, *format++);
		else
			check = write(1, format - 1, 1);
		if (check == -1)
			return (va_end(args), check);
		count += check;
	}
	return (va_end(args), count);
}
