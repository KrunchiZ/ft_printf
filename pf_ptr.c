/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_ptr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 17:34:41 by kchiang           #+#    #+#             */
/*   Updated: 2025/06/09 14:58:03 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	pf_ptr(va_list ap, t_spec mod)
{
	t_uint	ptr;
	char	*str;
	size_t	len;

	ptr = (t_uint)va_arg(ap, void *);
	if (!ptr && mod.fdwidth > 0)
		str = ft_strdup("(nil)");
	else if (!ptr && mod.fdwidth == 0)
		str = ft_strdup("");
	else
	{
		mod.flag |= ALT_FORM;
		str = ft_uitoa_base(ptr, LOWER_HEX_BASE);
		if (str && (mod.flag & HAS_PREC) && mod.precision > len)
			str = init_prec(str, mod, &len, 0);
	}
	if (!str)
		return (-1);
	if (mod.fdwidth < len)
		mod.fdwidth = len;
}
