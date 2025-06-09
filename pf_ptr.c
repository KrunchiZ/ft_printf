/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_ptr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 17:34:41 by kchiang           #+#    #+#             */
/*   Updated: 2025/06/09 12:59:22 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static char	*fill_zero(char *src, size_t prec, size_t *len)
{
	size_t	i;
	size_t	j;
	char	*host;

	i = 0;
	host = malloc(sizeof(char) * (prec + 1));
	if (!host)
		return (free(src), NULL);
	while (i < (prec - *len))
		host[i++] = '0';
	j = 0;
	while (i < prec)
		host[i++] = src[j++];
	host[i] = '\0';
	*len = prec;
	return (free(src), host);
}

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
			str = fill_zero(str, mod.precision, &len);
	}
	if (!str)
		return (-1);
	if (mod.fdwidth < len)
		mod.fdwidth = len;
}
