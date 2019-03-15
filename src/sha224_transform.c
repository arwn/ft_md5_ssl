/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 15:33:40 by zfaria            #+#    #+#             */
/*   Updated: 2019/03/15 10:46:47 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sha224.h>

void	sha224_transform(t_s256q *ctx, uint8_t *d)
{
	t_sql	s;

	sha224_transform_1(&s, d);
	s.a = ctx->state[0];
	s.b = ctx->state[1];
	s.c = ctx->state[2];
	s.d = ctx->state[3];
	s.e = ctx->state[4];
	s.f = ctx->state[5];
	s.g = ctx->state[6];
	s.h = ctx->state[7];
	sha224_transform_2(&s);
	ctx->state[0] += s.a;
	ctx->state[1] += s.b;
	ctx->state[2] += s.c;
	ctx->state[3] += s.d;
	ctx->state[4] += s.e;
	ctx->state[5] += s.f;
	ctx->state[6] += s.g;
	ctx->state[7] += s.h;
}

void	sha224_transform_1(t_sql *s, uint8_t *d)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < 16)
	{
		s->m[i] = (d[j] << 24) | (d[j + 1] << 16) |
			(d[j + 2] << 8) | (d[j + 3]);
		j += 4;
		i++;
	}
	while (i < 64)
	{
		s->m[i] = S1(s->m[i - 2]) + s->m[i - 7] +
			S0(s->m[i - 15]) + s->m[i - 16];
		i++;
	}
}

void	sha224_transform_2(t_sql *s)
{
	int i;

	i = 0;
	while (i < 64)
	{
		s->t1 = s->h + EP1(s->e) + CH(s->e, s->f, s->g) + g_k[i] + s->m[i];
		s->t2 = EP0(s->a) + MAJ(s->a, s->b, s->c);
		s->h = s->g;
		s->g = s->f;
		s->f = s->e;
		s->e = s->d + s->t1;
		s->d = s->c;
		s->c = s->b;
		s->b = s->a;
		s->a = s->t1 + s->t2;
		i++;
	}
}
