/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:40:41 by kchiang           #+#    #+#             */
/*   Updated: 2025/06/08 17:33:07 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include "libft.h"
# include <stdarg.h>

# define FLAG_SPEC		"-0.# +"
# define CONVERT_SPEC	"cspdiuxX%"
# define ALT_FORM		0b000001
# define ZERO_PAD		0b000010
# define LEFT_ALIGN		0b000100
# define ADD_SPACE		0b001000
# define SHOW_SIGN		0b010000
# define HAS_PREC		0b100000

/* Shorthands for unsigned variable types */
typedef unsigned char		t_uchar;
typedef unsigned int		t_uint;
typedef unsigned long		t_ulong;
typedef unsigned long long	t_ullong;

typedef struct s_spec
{
	t_uchar	flag;
	int		fdwidth;
	int		precision;
}							t_spec;

typedef int					(*t_fptr)(va_list, t_spec);

int	ft_printf(const char *format, ...);
int	pf_char(va_list ap, t_spec mod);
int	pf_string(va_list ap, t_spec mod);
int	pf_ptr(va_list ap, t_spec mod);
int	pf_int(va_list ap, t_spec mod);
int	pf_uint(va_list ap, t_spec mod);
int	pf_hexlower(va_list ap, t_spec mod);
int	pf_hexupper(va_list ap, t_spec mod);
int	pf_percent(va_list ap, t_spec mod);

#endif
