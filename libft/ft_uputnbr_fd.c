/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uputnbr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:47:57 by jpelline          #+#    #+#             */
/*   Updated: 2025/05/02 14:33:57 by jpelline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_uputnbr_fd(unsigned int n, int fd)
{
	size_t	count;
	int	check;

	count = 0;
	if (n > 9)
	{
		count += ft_uputnbr_fd(n / 10, fd);
		count += ft_uputnbr_fd(n % 10, fd);
	}
	else
	{
		check = ft_putchar_fd(n + '0', fd);
		if (check = -1)
			return (-1);
		count += check;
	}
	return (count);
}
