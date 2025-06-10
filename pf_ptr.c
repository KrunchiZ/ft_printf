/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_ptr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 17:34:41 by kchiang           #+#    #+#             */
/*   Updated: 2025/06/10 16:03:07 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	*parse_ptr(t_ulong ptr, t_spec *mod, size_t *len)
{
	char	*str;
	char	*tmp;

	mod->flag |= ALT_FORM;
	str = ft_uitoa_base(ptr, LOWER_HEX_BASE);
	if (!str)
		return (NULL);
	*len = ft_strlen(str);
	if ((mod->flag & HAS_PREC) && (mod->precision > *len))
	{
		tmp = ft_calloc((mod->precision) + 1, sizeof(char));
		if (!tmp)
			return (NULL);
		while ((*len)++ < (mod->precision))
			ft_strlcat(tmp, "0", mod->precision + 1);
		ft_strlcat(tmp, str, mod->precision + 1);
		free(str);
		str = tmp;
	}
	if (((mod->flag & SHOW_SIGN) && *str != '-')
		|| (mod->flag & ADD_SPACE))
		(*len)++;
	if (mod->flag & ALT_FORM)
		*len += 2;
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
		mod.flag &= LEFT_ALIGN;
	}
	else
		str = parse_ptr(ptr, &mod, &len);
	if (!str)
		return (-1);
	if (mod.fdwidth < len)
		mod.fdwidth = len;
	return (pf_digitstr(str, len, mod, 0));
}
