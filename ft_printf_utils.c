/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:04:02 by kchiang           #+#    #+#             */
/*   Updated: 2025/06/09 22:10:04 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	pf_prefix(t_spec mod)
{
	//check for ALT_FORM
	//check for SHOW_SIGN and ADD_SPACE
}

/* Prints digit string to stdout.
 * If ZERO_PAD, print '0' instead of space for fdwidth.
 * If fdwidth == len and ADD_SPACE is true, add a blank at the front.
 * */
int	exec_pf_digit(char *str, size_t len, t_spec mod)
{
	char	*pad;
	int		length;

	pad = " ";
	length = (int)(mod.fdwidth);
	if (mod.flag & ZERO_PAD)
		pad = "0";
	pf_prefix(mod);
	if (mod.flag & LEFT_ALIGN)
	{
		write(STDOUT_FILENO, str, len);
		while ((mod.fdwidth--) > len)
			write(STDOUT_FILENO, pad, 1);
	}
	else
	{
		while ((mod.fdwidth--) > len)
			write(STDOUT_FILENO, pad, 1);
		write(STDOUT_FILENO, str, len);
	}
	return (free(str), length);
}
