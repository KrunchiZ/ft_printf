/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_digitstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:04:02 by kchiang           #+#    #+#             */
/*   Updated: 2025/06/10 16:36:42 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/* Write a blank space or positive sign depending on the '+' or ' ' flag.
 * */
static void	pf_signspace(char *str, t_spec mod)
{
	if (((mod.flag & SHOW_SIGN) && *str != '-')
		|| (mod.flag & ADD_SPACE))
	{
		if (mod.flag & SHOW_SIGN)
			write(STDOUT_FILENO, "+", 1);
		else
			write(STDOUT_FILENO, " ", 1);
	}
	return ;
}

/* Write 0x or 0X for hexadecimal digits if there is '#' flag.
 * */
static void	pf_altform(t_spec mod, int is_uphex)
{
	if (mod.flag & ALT_FORM)
	{
		if (is_uphex)
			write(STDOUT_FILENO, "0X", 2);
		else
			write(STDOUT_FILENO, "0x", 2);
	}
	return ;
}

/* Zero paddings for field width if there is '0' flag.
 * */
static void	pf_zeropads(t_spec mod, size_t len)
{
	if (mod.flag & ZERO_PAD)
	{
		while (mod.fdwidth-- > len)
			write(STDOUT_FILENO, "0", 1);
	}
	return ;
}

/* Normal space padding for field width.
 * */
static void	pf_spacepads(t_spec mod, size_t len)
{
	if (!(mod.flag & ZERO_PAD))
	{
		while (mod.fdwidth-- > len)
			write(STDOUT_FILENO, " ", 1);
	}
	return ;
}

/* Prints digit string to stdout.
 * If ZERO_PAD, print '0' instead of space for fdwidth.
 * If fdwidth == len and ADD_SPACE is true, add a blank at the front.
 * */
int	pf_digitstr(char *str, size_t len, t_spec mod, int is_uphex)
{
	if (mod.flag & LEFT_ALIGN)
	{
		pf_signspace(str, mod);
		pf_altform(mod, is_uphex);
		pf_zeropads(mod, len);
		ft_putstr_fd(str, STDOUT_FILENO);
		pf_spacepads(mod, len);
	}
	else
	{
		pf_spacepads(mod, len);
		pf_signspace(str, mod);
		pf_altform(mod, is_uphex);
		pf_zeropads(mod, len);
		ft_putstr_fd(str, STDOUT_FILENO);
	}
	return (free(str), (int)mod.fdwidth);
}
