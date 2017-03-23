/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 17:19:30 by ntoniolo          #+#    #+#             */
/*   Updated: 2017/02/13 00:14:38 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <locale.h>
# include "../basic/includes/libft.h"
# include <stdlib.h>
# include <stdarg.h>
# include "../printf_fun/includes/printf_fun.h"

# define DIESE	0
# define MOINS	1
# define PLUS	2
# define SPACE	3
# define ZERO	4
# define PRECI	5

# define MOD_HH	1
# define MOD_H	2
# define MOD_J	3
# define MOD_Z	4
# define MOD_L	5
# define MOD_LL	6
# define MOD_LLL 7

# define BUFF_SIZE_P 10

typedef struct	s_option
{
	long long int	len;
	va_list			ap;
	int				flags[7];
	long long int	width;
	long long int	preci;
	int				mod;
	char			*nb_c;
	wchar_t			*word_w;
	char			*word_c;
	char			*prefix;
	char			*before;
	int				size_flags;
	int				size_arg;
	int				sign;
	char			*final;
	int				final_len;
	int				b;
	char			buffer[BUFF_SIZE_P];
	int				sub_word;
}				t_option;

int				ft_printf(char *str, ...);
int				check_flags(char *str, t_option *option);
void			ft_putbuffer(t_option *option);
void			ft_putbufferchar(char c, t_option *option);

int				sc_c(char *str, t_option *option);
int				sc_s(char *str, t_option *option);
int				dipfoux(char *str, t_option *option);
void			mod_uox(char *str, t_option *option);
void			mod_di(char *str, t_option *option);
void			mod_dipfoux(char *str, t_option *option);
int				write_other(char *str, t_option *option);
int				write_percent(char *str, t_option *option);

int				can_i_write_width(char *str, t_option *option);
char			*write_width(t_option *option);
char			*write_width_0(char *str, t_option *option);
int				preci_sc(char *str, t_option *option);
int				preci_dioux(char *str, t_option *option);
int				write_f(char *str, t_option *option, long double nb);
int				write_dipoux(char *str, t_option *option, long long int nb);

#endif
