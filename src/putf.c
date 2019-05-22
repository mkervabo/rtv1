/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 15:23:10 by dde-jesu          #+#    #+#             */
/*   Updated: 2019/05/22 10:59:17 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putf_va(int fd, char *fmt, va_list args)
{
	char	*l_fmt;

	l_fmt = fmt;
	while ((fmt = ft_strchr(fmt, '%')) && *++fmt)
	{
		write(fd, l_fmt, fmt - l_fmt - 1);
		if (*fmt == '%')
			ft_putchar_fd('%', fd);
		else if (*fmt == 'd')
			ft_putnbr_fd(va_arg(args, int), fd);
		else if (*fmt == 's')
			ft_putstr_fd(va_arg(args, char *), fd);
		else if (*fmt == 'c')
			ft_putchar_fd((char)va_arg(args, int), fd);
		l_fmt = ++fmt;
	}
	ft_putstr_fd(l_fmt, fd);
}