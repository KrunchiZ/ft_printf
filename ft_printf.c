/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:47:09 by kchiang           #+#    #+#             */
/*   Updated: 2025/10/22 19:55:40 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "libftprintf.h"

/* Calls the pf functions based on their respective conversion specifier.
 * */
static t_fptr	fetch_pf(const char sp)
{
	t_fptr	list[256];

	list['c'] = pf_char;
	list['s'] = pf_string;
	list['p'] = pf_ptr;
	list['d'] = pf_int;
	list['i'] = pf_int;
	list['u'] = pf_int;
	list['x'] = pf_lowerhex;
	list['X'] = pf_upperhex;
	list['%'] = pf_percent;
	return (list[(int)sp]);
}

/* Using bits as boolean switches for the specifier flags 
 * Zero-padding will be turn on only if there is no left align and precision
 * */
static void	parse_flag(const char c, t_spec *mod)
{
	if (c == '-')
		mod->flag |= LEFT_ALIGN;
	else if (c == '#')
		mod->flag |= ALT_FORM;
	else if (c == '.')
		mod->flag |= HAS_PREC;
	else if (c == '0')
		mod->flag |= ZERO_PAD;
	else if (c == '+')
		mod->flag |= SHOW_SIGN;
	else if (c == ' ')
		mod->flag |= ADD_SPACE;
	if (mod->flag & ADD_SPACE && mod->flag & SHOW_SIGN)
		mod->flag &= ~ADD_SPACE;
	if (mod->flag & ZERO_PAD
		&& ((mod->flag & LEFT_ALIGN) || (mod->flag & HAS_PREC)))
		mod->flag &= ~ZERO_PAD;
	return ;
}

/* Using parse_flag, iterate through format and turn on the corresponding
 * bit of mod->flag according to FLAG_SPEC.
 *
 * fdwidth and precision will be parsed using ft_atoi.
 * */
static void	parse_mod(const char **format, t_spec *mod)
{
	while (ft_strchr(FLAG_SPEC, **format))
		parse_flag(*(*format)++, mod);
	if (ft_isdigit(**format))
		mod->fdwidth = (int)ft_atoi(*format);
	while (ft_isdigit(**format))
		(*format)++;
	if (**format == '.')
	{
		parse_flag(*(*format)++, mod);
		if (ft_isdigit(**format))
			mod->precision = (int)ft_atoi(*format);
		while (ft_isdigit(**format))
			(*format)++;
	}
	return ;
}

/* Iterates through format and parse the flags (FLAG_SPEC), fdwidth and
 * precision into t_spec mod using parse_mod.
 *
 * If the following conversion specifier matches CONVERT_SPEC,
 * it is deemed valid and the corresponding pf_func. will be fetched to
 * the func.ptr 'pf'.
 *
 * Invalid specifier will be treated as a normal string literal.
 * */
static int	init_pf(const char **format, va_list *ap)
{
	t_spec		mod;
	t_fptr		pf;
	const char	*start;

	start = *format;
	mod = (t_spec){0};
	parse_mod(format, &mod);
	if (ft_strchr(CONVERT_SPEC, **format))
	{
		pf = fetch_pf(*(*format)++);
		return (pf(ap, mod));
	}
	write(STDOUT_FILENO, "%", 1);
	*format = start;
	return (1);
}

/* ft_printf iterates through format and write characters to stdout.
 * When % is met, init_pf to parse the flags, fdwidth and precisions(if any)
 * into a struct named t_spec.
 * If specifier is invalid, % will be printed like a normal string literal.
 *
 * 'ap' will be the obj containing the variable argument list with
 * a pointer pointing at the first argument.
 * and will be accessed by the pf functions using va_arg macro.
 *
 * Total string length will be returned upon successful execution.
 * On error, return (-1).
 * */
int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		len;
	int		pf_len;

	va_start(ap, format);
	len = 0;
	if (!format)
		return (va_end(ap), -1);
	while (*format)
	{
		if (*format != '%')
		{
			write(STDOUT_FILENO, format++, 1);
			len++;
		}
		else
		{
			format++;
			pf_len = init_pf(&format, &ap);
			if (pf_len < 0)
				return (va_end(ap), -1);
			len += pf_len;
		}
	}
	return (va_end(ap), len);
}
