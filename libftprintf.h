/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:40:41 by kchiang           #+#    #+#             */
/*   Updated: 2025/06/05 16:18:03 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include "libft.h"
# include <stdarg.h>

# define CONVERT_SPEC "cspdiuxX%"
# define ALT_FORM 0b00000001
# define ZERO_PAD 0b00000010

/* Shorthands for unsigned variable types */
typedef unsigned char		t_uchar;
typedef unsigned int		t_uint;
typedef unsigned long		t_ulong;
typedef unsigned long long	t_ullong;

typedef struct s_modifier
{
	t_uint	flags;
	int		fdwidth;
	int		precision;
}							t_modifier;

typedef int					(*t_fptr)(va_list, );

#endif
