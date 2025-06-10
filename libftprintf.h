/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:40:41 by kchiang           #+#    #+#             */
/*   Updated: 2025/06/11 01:32:47 by kchiang          ###   ########.fr       */
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
# define LOWER_HEX_BASE	"0123456789abcdef"
# define UPPER_HEX_BASE	"0123456789ABCDEF"

typedef struct s_spec
{
	t_uchar	flag;
	size_t	fdwidth;
	size_t	precision;
}			t_spec;

/* Function pointer to call the specifier functions */
typedef int	(*t_fptr)(va_list, t_spec);

/* Main Function */
int		ft_printf(const char *format, ...);

/* Util Function */
int		ft_putnbrstr(char *str, size_t len, t_spec mod, int is_uphex);

/* To be called by t_fptr. */
/* Functions for their respective conversion specifier. */
int		pf_char(va_list ap, t_spec mod);
int		pf_string(va_list ap, t_spec mod);
int		pf_ptr(va_list ap, t_spec mod);
int		pf_int(va_list ap, t_spec mod);
int		pf_uint(va_list ap, t_spec mod);
int		pf_lowerhex(va_list ap, t_spec mod);
int		pf_upperhex(va_list ap, t_spec mod);
int		pf_percent(va_list ap, t_spec mod);

#endif
