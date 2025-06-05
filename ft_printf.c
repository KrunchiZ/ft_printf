/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:47:09 by kchiang           #+#    #+#             */
/*   Updated: 2025/06/05 17:58:48 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	check_spec(char **format, va_list ap, int len)
{
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		len;

	va_start(ap, format);
	len = 0;
	while (*format)
	{
		if (*format != '%')
		{
			write(STDIN_FILENO, format++, 1);
			len++;
		}
		else
		{
			format++;//move past '%'
			len = check_spec(&format, ap, len);
		//^check for flags, field width, precision then conversion specifier
		}
	}
	va_end(ap);
	return (len);
}
