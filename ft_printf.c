/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchiang <kchiang@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:47:09 by kchiang           #+#    #+#             */
/*   Updated: 2025/06/07 00:19:37 by kchiang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/* call the pf functions based on their respective conversion specifier */
static t_fptr	fetch_pf(const char sp)
{
	t_fptr	list[256];

	list['c'] = pf_char;
	list['s'] = pf_string;
	list['p'] = pf_ptr;
	list['d'] = pf_int;
	list['i'] = pf_int;
	list['u'] = pf_uint;
	list['x'] = pf_hexlower;
	list['X'] = pf_hexupper;
	list['%'] = pf_percent;
	return (list[(int)sp]);
}

/* Using bits as boolean switches for the specifier flags 
 * Zero-padding will be turn on only if there is no left align and precision
 * */
static void	parse_flag(const char c, t_spec *mod)
{
	mod->flag = 0;
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
	if (mod->flag & ZERO_PAD &&
		((mod->flag & LEFT_ALIGN) || (mod->flag & HAS_PREC)))
		mod->flag &= ~ZERO_PAD;
	return ;
}

static int	check_spec(const char **format, va_list ap, int len)
{
	t_spec	mod;
	t_fptr	pf;

	while (ft_strchr(FLAG_SPEC, **format))
		parse_flag(*(*format)++, &mod);
	if (ft_isdigit(**format))
		mod.fdwidth = ft_atoi(*format);
	while (ft_isdigit(**format))
		(*format)++;
	if (**format == '.')
		parse_flag(*(*format)++, &mod);
	if (ft_isdigit(**format))
		mod.precision = ft_atoi(*format);
	while (ft_isdigit(**format))
		(*format)++;
	if (ft_strchr(CONVERT_SPEC, **format))
		pf = fetch_pf(*(*format)++);
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		len;

	va_start(ap, format);
	len = 0;
	while (*format)
	{
		if (*format != '%')
		{
			write(STDIN_FILENO, format++, 1);
			len++;
		}
		else
		{
			format++;//move past '%'
			len = check_spec(&format, ap, len);
			if (len < 0)
				break ;
		}
	}
	va_end(ap);
	return (len);
}
