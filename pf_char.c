/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_char.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 13:55:14 by kchiang           #+#    #+#             */
/*   Updated: 2025/06/24 17:56:18 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/* Convert int/char as unsigned char and print.
 * All flags and precision will be ignored except left align and
 * fdwidth (blank spacing).
 * */
int	pf_char(va_list *ap, t_spec mod)
{
	t_uchar	ch;
	int		len;

	ch = (t_uchar)va_arg(*ap, int);
	len = 1;
	if (!(mod.flag & LEFT_ALIGN))
	{
		while (mod.fdwidth-- > 1)
		{
			write(STDOUT_FILENO, " ", 1);
			len++;
		}
		write(STDOUT_FILENO, &ch, 1);
	}
	else
	{
		write(STDOUT_FILENO, &ch, 1);
		while (mod.fdwidth-- > 1)
		{
			write(STDOUT_FILENO, " ", 1);
			len++;
		}
	}
	return (len);
}
