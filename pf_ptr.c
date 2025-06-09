/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_ptr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 17:34:41 by kchiang           #+#    #+#             */
/*   Updated: 2025/06/09 19:02:23 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/* For digit strings, if precision > the s length, the front of the string
 * will be padded with zeroes.
 * New malloc string will be returned and s will be freed.
 * */
static char	*init_precision(char *s, t_spec mod, size_t *len, int is_uphex)
{
	size_t	i;
	size_t	j;
	char	*host;

	if (mod.flag & ALT_FORM)
		mod.precision += 2;
	host = ft_calloc(mod.precision + 1, sizeof(char));
	if (!host)
		return (free(s), NULL);
	i = 0;
	if (mod.flag & ALT_FORM)
	{
		if (is_uphex)
			ft_strlcpy(host, "0X", 2);
		else
			ft_strlcpy(host, "0x", 2);
		i += 2;
	}
	while (i < (mod.precision - *len))
		host[i++] = '0';
	j = 0;
	while (i < mod.precision)
		host[i++] = s[j++];
	*len = mod.precision;
	return (free(s), host);
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
	{
		mod.flag |= ALT_FORM;
		str = pf_uitoa_base(ptr, LOWER_HEX_BASE, &len);
		if (str && (mod.flag & HAS_PREC) && mod.precision > len)
			str = init_precision(str, mod, &len, 1);
	}
	if (mod.fdwidth < len)
		mod.fdwidth = len;
	if (str)
		return (exec_pf_digit(str, len, mod));
	return (-1);
}
