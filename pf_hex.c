/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 17:34:41 by kchiang           #+#    #+#             */
/*   Updated: 2025/06/24 17:58:05 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static char	*parse_hex(t_ullong nb, t_spec *mod, int *len)
{
	char	*str;

	if (mod->is_uphex)
		str = ft_uitoa_base(nb, UPPER_HEX_BASE);
	else
		str = ft_uitoa_base(nb, LOWER_HEX_BASE);
	if (!str)
		return (NULL);
	*len = (int)ft_strlen(str);
	if ((mod->flag & HAS_PREC) && (mod->precision > *len))
	{
		str = init_prec(str, mod, len);
		if (!str)
			return (NULL);
	}
	if (mod->flag & ALT_FORM)
		*len += 2;
	return (str);
}

/* Prints unsigned hexadecimal in uppercases.
 * SHOW_SIGN and ADD_SPACE are ignored.
 * Prints nothing if both nb and precision are 0.
 * */
int	pf_upperhex(va_list *ap, t_spec mod)
{
	t_ullong	nb;
	char		*str;
	int			len;

	nb = (t_ullong)va_arg(*ap, t_uint);
	len = 0;
	mod.is_uphex = 1;
	mod.flag &= (~SHOW_SIGN & ~ADD_SPACE);
	if (!nb)
		mod.flag &= ~ALT_FORM;
	if (!nb && ((mod.flag & HAS_PREC) && !(mod.precision)))
	{
		str = ft_strdup("");
		mod.flag &= LEFT_ALIGN;
	}
	else
		str = parse_hex(nb, &mod, &len);
	if (!str)
		return (-1);
	if (mod.fdwidth < len)
		mod.fdwidth = len;
	return (ft_putnbrstr(str, len, mod));
}

/* Prints unsigned hexadecimal in lowercases.
 * SHOW_SIGN and ADD_SPACE are ignored.
 * Prints nothing if both nb and precision are 0.
 * */
int	pf_lowerhex(va_list *ap, t_spec mod)
{
	t_ullong	nb;
	char		*str;
	int			len;

	nb = (t_ullong)va_arg(*ap, t_uint);
	len = 0;
	mod.flag &= (~SHOW_SIGN & ~ADD_SPACE);
	if (!nb)
		mod.flag &= ~ALT_FORM;
	if (!nb && ((mod.flag & HAS_PREC) && !(mod.precision)))
	{
		str = ft_strdup("");
		mod.flag &= LEFT_ALIGN;
	}
	else
		str = parse_hex(nb, &mod, &len);
	if (!str)
		return (-1);
	if (mod.fdwidth < len)
		mod.fdwidth = len;
	return (ft_putnbrstr(str, len, mod));
}
