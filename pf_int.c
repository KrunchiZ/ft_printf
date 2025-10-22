/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_int.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 17:34:41 by kchiang           #+#    #+#             */
/*   Updated: 2025/10/22 19:56:32 by kchiang          ###   ########.fr       */
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

static char	*parse_uint(t_ullong nb, t_spec *mod, int *len)
{
	char	*str;

	str = ft_uitoa(nb);
	if (!str)
		return (NULL);
	*len = (int)ft_strlen(str);
	if ((mod->flag & HAS_PREC) && (mod->precision > *len))
	{
		str = init_prec(str, mod, len);
		if (!str)
			return (NULL);
	}
	return (str);
}

static char	*parse_int(t_llong nb, t_spec *mod, int *len)
{
	char	*str;

	if (nb < 0)
	{
		mod->is_neg = 1;
		nb = -nb;
	}
	str = ft_itoa(nb);
	if (!str)
		return (NULL);
	*len = (int)ft_strlen(str);
	if ((mod->flag & HAS_PREC) && (mod->precision > *len))
	{
		str = init_prec(str, mod, len);
		if (!str)
			return (NULL);
	}
	if (mod->is_neg)
		(*len)++;
	return (str);
}

/* Prints unsigned integer to stdout.
 * SHOW_SIGN, ADD_SPACE and ALT_FORM are ignored.
 * Prints nothing if both nb and precision are 0.
 * */
int	pf_uint(va_list *ap, t_spec mod)
{
	t_ullong	nb;
	char		*str;
	int			len;

	nb = (t_ullong)va_arg(*ap, t_uint);
	len = 0;
	mod.flag &= (~SHOW_SIGN & ~ADD_SPACE & ~ALT_FORM);
	if (!nb && ((mod.flag & HAS_PREC) && !(mod.precision)))
		str = ft_strdup("");
	else
		str = parse_uint(nb, &mod, &len);
	if (!str)
		return (-1);
	if (mod.fdwidth < len)
		mod.fdwidth = len;
	return (ft_putnbrstr(str, len, mod));
}

/* Prints signed int to stdout.
 * ALT_FORM is ignored.
 * Prints nothing if both nb and precision are 0.
 * */
int	pf_int(va_list *ap, t_spec mod)
{
	t_llong	nb;
	char	*str;
	int		len;

	nb = (t_llong)va_arg(*ap, int);
	len = 0;
	mod.flag &= ~ALT_FORM;
	if (!nb && ((mod.flag & HAS_PREC) && !(mod.precision)))
		str = ft_strdup("");
	else
		str = parse_int(nb, &mod, &len);
	if (!str)
		return (-1);
	if (((mod.flag & SHOW_SIGN) || (mod.flag & ADD_SPACE)) && !(mod.is_neg))
		len++;
	if (mod.fdwidth < len)
		mod.fdwidth = len;
	return (ft_putnbrstr(str, len, mod));
}
