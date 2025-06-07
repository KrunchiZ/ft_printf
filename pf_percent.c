/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_percent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 15:41:11 by kchiang           #+#    #+#             */
/*   Updated: 2025/06/07 18:27:20 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/* Print '%' to stdout ignoring all fags, fdwidth and precision.
 * */
int	pf_percent(va_list ap, t_spec mod)
{
	(void)ap;
	(void)mod;
	write(STDOUT_FILENO, "%", 1);
	return (1);
}
