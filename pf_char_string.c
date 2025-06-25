/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_char_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 13:55:14 by kchiang           #+#    #+#             */
/*   Updated: 2025/06/25 18:12:06 by kchiang          ###   ########.fr       */
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

/* If LEFT_ALIGN is on, print str followed by blank spaces up to fdwidth.
 * Else, blank spaces first.
 * */
static void	exec_pf_string(char *str, int len, t_spec mod)
{
	if (mod.flag & LEFT_ALIGN)
	{
		write(STDOUT_FILENO, str, len);
		while ((mod.fdwidth--) > len)
			write(STDOUT_FILENO, " ", 1);
	}
	else
	{
		while ((mod.fdwidth--) > len)
			write(STDOUT_FILENO, " ", 1);
		write(STDOUT_FILENO, str, len);
	}
	return ;
}

/* exec_pf_string to print str to the stdout.
 *
 * fdwidth is the total space for the output.
 * If fdwidth < strlen, fdwidth = strlen.
 * precision determines the printable character number of string.
 *
 * if str is NULL, prints "(null)" except when precision is present and
 * precision < 6, prints nothing (empty string).
 * */
int	pf_string(va_list *ap, t_spec mod)
{
	char	*str;
	int		len;

	str = va_arg(*ap, char *);
	if (!str && (mod.flag & HAS_PREC) && mod.precision < 6)
		str = "";
	else if (!str)
		str = "(null)";
	len = (int)ft_strlen(str);
	if ((mod.flag & HAS_PREC) && mod.precision < len)
		len = mod.precision;
	if (mod.fdwidth < len)
		mod.fdwidth = len;
	exec_pf_string(str, len, mod);
	return (mod.fdwidth);
}
