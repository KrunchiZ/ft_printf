/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:50:51 by kchiang           #+#    #+#             */
/*   Updated: 2025/06/11 17:35:22 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

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
int	pf_string(va_list ap, t_spec mod)
{
	char	*str;
	int		len;

	str = va_arg(ap, char *);
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
