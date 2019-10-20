/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caellis <caellis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 18:46:01 by bnesoi            #+#    #+#             */
/*   Updated: 2019/09/05 12:29:44 by caellis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdlib.h>
# include <errno.h>
# include <stdio.h>
# include <unistd.h>
# include <stdint.h>
# include <float.h>

# define BUFF_SIZE 42
# define PF_LM_MAXLEN 12000

typedef union		u_80bits
{
	long double		n;
	struct
	{
		uint64_t	man:64;
		uint16_t	exp:15;
		uint8_t		sign:1;
	}				bits;
}					t_80bits;

typedef struct		s_real_num
{
	t_80bits		r_num;
	int16_t			r_n_exp;
	uint16_t		r_long_int[PF_LM_MAXLEN];
	uint16_t		r_long_frac[PF_LM_MAXLEN];
}					t_pf_real;

typedef struct		s_pf_format
{
	va_list			va_args;
	char			*fmt;
	int				fd;

	char			cv;
	unsigned int	flg;
	int				prc;
	int				pad;
	char			pad_c;
	int				error;

	char			buff[BUFF_SIZE];
	size_t			buff_size;
	char			*dest;
	int				len;
}					t_pf_format;

# define PF_F_SPACE  (1u << 0u)
# define PF_F_PLUS   (1u << 1u)
# define PF_F_LEFTJ  (1u << 2u)
# define PF_F_SHORT  (1u << 3u)
# define PF_F_CHAR   (1u << 4u)
# define PF_F_LLONG  (1u << 5u)
# define PF_F_LONG   (1u << 6u)
# define PF_F_LONGD  (1u << 7u)
# define PF_F_ALT    (1u << 8u)
# define PF_F_ZERO   (1u << 9u)
# define PF_F_GROUP	 (1u << 10u)
# define PF_F_I18N	 (1u << 11u)
# define PF_F_PRC    (1u << 12u)
# define PF_F_IMAX   (1u << 13u)
# define PF_F_SIZE   (1u << 14u)

# define PF_NUM(v) ((v) >= '0' && (v) <= '9')
# define PF_TO_UP(c)(((c) >= 'a' && (c) <= 'z') ? c - 32 : c)
# define PF_BASE "0123456789abcdef"

# define PF_MAX_D_PREC 16
# define PF_D_PREC 6
# define PF_D_S (1u << 63u)
# define PF_D_EXP_E 0x7FFFu
# define PF_D_EXP_BIAS 16383
# define PF_D_MAN 0xFFFFFFFFFFFFFu
# define PF_LM_BASE 10
# define PF_LM_2POW12 4096
# define PF_LM_5POW5 3125
# define PF_LM_MAXMUL 7281
# define PF_LM_MAXPREC 19

# define PF_CSI "di"
# define PF_CUI "oOuUxX"
# define PF_CI PF_CSI PF_CUI
# define PF_CF "f"
# define PF_CE "e"
# define PF_CC "c"
# define PF_CS "sS"
# define PF_CP "p"
# define PF_C "%" PF_CI PF_CUI PF_CF PF_CC PF_CS PF_CP

int					ft_printf(const char *format, ...);
int					ft_fprintf(int fd, const char *format, ...);
int					ft_sprintf(char *dest, const char *format, ...);

void				pf_put_format(t_pf_format *f);
void				pf_parse_format(t_pf_format *f);
void				pf_put_buffered(const char *str, t_pf_format *f,
	size_t size, int flush_buffer);

void				pf_put_int(t_pf_format *f);
void				pf_put_float(t_pf_format *f);
void				pf_put_char(t_pf_format *f);
void				pf_put_string(t_pf_format *f);
void				pf_put_ptr(t_pf_format *f);
void				pf_put_empty(t_pf_format *f);

void				pf_put_int_prefix(int is_neg, int is_zero, int len,
	t_pf_format *f);
void				pf_put_pad(t_pf_format *f);

uintmax_t			pf_u_power(uintmax_t nb, int p);
int16_t				pf_u_exp_power(int16_t nb, int p);
int					is_not_realnum(t_pf_real *real, t_pf_format *f);
int16_t				pf_lm_checktrailing(uint16_t longn[], int16_t pos);
void				pf_fast_bzero(void *s, size_t n);
int					pf_in(const char *s, char c);
size_t				pf_strlen(const char *s);
void				pf_bzero(void *s, size_t n);
void				pf_strreverse(char *str);
int					pf_atoi(const char *nptr);
char				*pf_strcpy(char *dst, const char *src);

void				pf_lm_add(uint16_t long_a[], uint16_t long_b[],
	int16_t shift);
int16_t				pf_lm_power(uint16_t result[], int16_t exp,
		uint8_t is_denorm);
void				pf_lm_add_one(uint16_t long_a[], uint32_t int_b);
#endif
