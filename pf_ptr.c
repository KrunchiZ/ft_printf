/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_ptr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 17:34:41 by kchiang           #+#    #+#             */
/*   Updated: 2025/10/22 19:56:55 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "libftprintf.h"

static char	*init_prec(char *str, t_spec *mod, int *len)
{
	char	*tmp;

	tmp = ft_calloc((mod->precision) + 1, sizeof(char));
	if (!tmp)
		return (NULL);
	while (*len < (mod->precision))
	{
		ft_strlcat(tmp, "0", mod->precision + 1);
		(*len)++;
	}
	ft_strlcat(tmp, str, mod->precision + 1);
	free(str);
	str = tmp;
	return (str);
}

static char	*parse_ptr(t_ulong ptr, t_spec *mod, int *len)
{
	char	*str;

	mod->flag |= ALT_FORM;
	str = ft_uitoa_base(ptr, LOWER_HEX_BASE);
	if (!str)
		return (NULL);
	*len = (int)ft_strlen(str);
	if ((mod->flag & HAS_PREC) && (mod->precision > *len))
	{
		str = init_prec(str, mod, len);
		if (!str)
			return (NULL);
	}
	if ((mod->flag & SHOW_SIGN) || (mod->flag & ADD_SPACE))
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
int	pf_ptr(va_list *ap, t_spec mod)
{
	t_ullong	ptr;
	char		*str;
	int			len;

	ptr = (t_ullong)va_arg(*ap, void *);
	len = 0;
	if (!ptr)
	{
		str = ft_strdup(NULL_PTR);
		len = 5;
		mod.flag &= LEFT_ALIGN;
	}
	else
		str = parse_ptr(ptr, &mod, &len);
	if (!str)
		return (-1);
	if (mod.fdwidth < len)
		mod.fdwidth = len;
	return (ft_putnbrstr(str, len, mod));
}
