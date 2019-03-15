/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 11:16:43 by zfaria            #+#    #+#             */
/*   Updated: 2019/03/15 12:07:06 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA1_H
# define SHA1_H

# include <stdlib.h>
# define ROTLEFT(a, b) ((a << b) | (a >> (32 - b)))

typedef struct	s_s
{
	uint8_t		data[64];
	uint32_t	datalen;
	uint64_t	bitlen;
	uint32_t	state[5];
	uint32_t	k[4];
}				t_s1ctx;

typedef struct	s_sql
{
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
	uint32_t	e;
	uint32_t	t;
	uint32_t	m[80];
}				t_sql;

void			sha1_init(t_s1ctx *ctx);
void			sha1_update(t_s1ctx *ctx, uint8_t *data, uint64_t len);
void			sha1_final(t_s1ctx *ctx, uint8_t *hash);
void			sha1_transform_1(t_s1ctx *ctx, uint8_t *data, t_sql *s);
void			sha1_transform_2(t_s1ctx *ctx, t_sql *s);
void			sha1_transform_3(t_s1ctx *ctx, t_sql *s);

#endif
