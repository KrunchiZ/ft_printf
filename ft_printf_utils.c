/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:04:02 by kchiang           #+#    #+#             */
/*   Updated: 2025/06/09 14:57:43 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/* For digit strings, if precision > the s length, the front of the string
 * will be padded with zeroes.
 * New malloc string will be returned and s will be freed.
 * */
char	*init_precision(char *s, t_spec mod, size_t *len, int is_uphex)
{
	size_t	i;
	size_t	j;
	char	*host;

	if (mod.flag & ALT_FORM)
		mod.precision += 2;
	host = ft_calloc(mod.precision + 1, sizeof(char));
	if (!host)
		return (free(src), NULL);
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
