/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:04:02 by kchiang           #+#    #+#             */
/*   Updated: 2025/06/10 13:31:12 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	pf_signspace(char *str, t_spec *mod, size_t *len)
{
	if (((mod->flag & SHOW_SIGN) && *str != '-')
		|| (mod->flag & ADD_SPACE))
	{
		if (mod->flag & SHOW_SIGN)
			write(STDOUT_FILENO, "+", 1);
		else
			write(STDOUT_FILENO, " ", 1);
		mod->fdwidth--;
		(*len)++;
	}
	return ;
}

static void	pf_prefix(t_spec *mod, size_t *len, int is_uphex)
{
	if (mod->flag & ALT_FORM)
	{
		if (is_uphex)
			write(STDOUT_FILENO, "0X", 2);
		else
			write(STDOUT_FILENO, "0x", 2);
		mod->fdwidth -= 2;
		*len += 2;
	}
	return ;
}

static void	pf_zeropad(t_spec *mod, size_t *len)
{
	if (mod->flag & ZERO_PAD)
	return ;
}

/* Prints digit string to stdout.
 * If ZERO_PAD, print '0' instead of space for fdwidth.
 * If fdwidth == len and ADD_SPACE is true, add a blank at the front.
 * */
int	exec_pf_digitstr(char *str, size_t len, t_spec mod, int	is_uphex)
{
	int	rt_len;

	if (mod.flag & LEFT_ALIGN)
	{
		pf_signspace(str, &mod);
		pf_prefix(&mod, is_uphex);
		pf_zeropad(&mod, len);
		ft_putstr_fd(str, STDOUT_FILENO);
		while (((mod.fdwidth--) > len) && !(mod.flag & ZERO_PAD))
			write(STDOUT_FILENO, " ", 1);
	}
	else
	{
		while ((mod.fdwidth--) > len)
			write(STDOUT_FILENO, pad, 1);
		ft_putstr_fd(str, STDOUT_FILENO);
	}
	return (free(str), rt_len);
}
