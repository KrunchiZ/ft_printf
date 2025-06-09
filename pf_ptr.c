/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_ptr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 17:34:41 by kchiang           #+#    #+#             */
/*   Updated: 2025/06/10 00:24:20 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/* ft_strlen to determine the base system of base string.
 * If base length is less than 2, base system is invalid, return NULL.
 * Else, init_itoa_base.
 * */
static char	*uitoa_base(t_ullong nbr, const char *base, size_t *len)
{
	size_t	base_len;
	char	tmp[65];
	int		depth;

	base_len = ft_strlen(base);
	depth = 64;
	tmp[depth] = '\0';
	tmp[63] = base[0];
	if (nbr == 0)
	{
		*len = 1;
		return (ft_strdup(&tmp[63]));
	}
	while (nbr)
	{
		tmp[--depth] = base[nbr % base_len];
		nbr /= base_len;
	}
	*len = ft_strlen(&tmp[depth]);
	return (ft_strdup(&tmp[depth]));
}

static void	*parse_ptr(t_ulong ptr, t_spec *mod, size_t *len)
{
	char	*str;
	int		is_uphex;
	char	*host;

	mod->flag |= ALT_FORM;
	str = uitoa_base(ptr, LOWER_HEX_BASE, len);
	if (!str)
		return (NULL);
	if (mod->precision < *len)
		mod->precision = *len;
	return (str);
}

/* Prints pointers like %x(unsigned int) specifier with ALT_FORM.
 *
 * Prints nothing if ptr is NULL and precision is 0.
 * Else, print (nil) for NULL.
 * */
int	pf_ptr(va_list ap, t_spec mod)
{
	t_ulong	ptr;
	char	*str;
	size_t	len;

	ptr = (t_ulong)va_arg(ap, void *);
	len = 0;
	if (!ptr && mod.fdwidth > 0)
	{
		str = ft_strdup("(nil)");
		len = 5;
	}
	else if (!ptr && mod.fdwidth == 0)
		str = ft_strdup("");
	else
		str = parse_ptr(ptr, &mod, &len);
	if (!str)
		return (-1);
	if (mod.flag & ALT_FORM)
		len += 2;
	if ((mod.flag & SHOW_SIGN) || (mod.flag & ADD_SPACE))
		len += 1;
	if (mod.fdwidth < len)
		mod.fdwidth = len;
	return (exec_pf_digit(str, len, mod));
}
