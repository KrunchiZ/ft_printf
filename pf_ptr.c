/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_ptr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 17:34:41 by kchiang           #+#    #+#             */
/*   Updated: 2025/06/09 22:10:03 by kchiang          ###   ########.fr       */
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

	host = ft_calloc(*len + 1, sizeof(char));
	if (!host)
		return (free(s), NULL);
	i = 0;
	while ((mod.flag & HAS_PREC) && (i < (mod.precision - *len)))
		host[i++] = '0';
	j = 0;
	while (i < mod.precision)
		host[i++] = s[j++];
	*len = mod.precision;
	return (free(s), host);
}

static void	*parse_ptr(t_ulong ptr, t_spec *mod, size_t *len)
{
	char	*str;
	int		is_uphex;

	mod->flag |= ALT_FORM;
	str = pf_uitoa_base(ptr, LOWER_HEX_BASE, len);
	if (mod->precision < *len)
		mod->precision = *len;
	is_uphex = 0;
	if (str)
		str = init_precision(str, *mod, len, is_uphex);
	if (NULL)
		return (NULL);
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
