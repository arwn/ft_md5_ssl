/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha1_transform.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 11:36:43 by zfaria            #+#    #+#             */
/*   Updated: 2019/03/15 12:11:32 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sha1.h>

void	sha1_transform_1(t_s1ctx *ctx, uint8_t *data, t_sql *s)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < 16)
	{
		s->m[i] = (data[j] << 24) + (data[j + 1] << 16) + (data[j + 2] << 8) +
			(data[j + 3]);
		i++;
		j += 4;
	}
	while (i < 80)
	{
		s->m[i] = (s->m[i - 3] ^ s->m[i - 8] ^ s->m[i - 14] ^ s->m[i - 16]);
		s->m[i] = (s->m[i] << 1) | (s->m[i] >> 31);
		i++;
	}
	s->a = ctx->state[0];
	s->b = ctx->state[1];
	s->c = ctx->state[2];
	s->d = ctx->state[3];
	s->e = ctx->state[4];
}

void	sha1_transform_2(t_s1ctx *ctx, t_sql *s)
{
	int i;

	i = 0;
	while (i < 20)
	{
		s->t = ROTLEFT(s->a, 5) + ((s->b & s->c) ^ (~s->b & s->d)) +
			s->e + ctx->k[0] + s->m[i];
		s->e = s->d;
		s->d = s->c;
		s->c = ROTLEFT(s->b, 30);
		s->b = s->a;
		s->a = s->t;
		i++;
	}
	while (i < 40)
	{
		s->t = ROTLEFT(s->a, 5) + (s->b ^ s->c ^ s->d) + s->e +
			ctx->k[1] + s->m[i];
		s->e = s->d;
		s->d = s->c;
		s->c = ROTLEFT(s->b, 30);
		s->b = s->a;
		s->a = s->t;
		i++;
	}
}

void	sha1_transform_3(t_s1ctx *ctx, t_sql *s)
{
	int i;

	i = 40;
	while (i < 60)
	{
		s->t = ROTLEFT(s->a, 5) + ((s->b & s->c) ^ (s->b & s->d) ^
			(s->c & s->d)) + s->e + ctx->k[2] + s->m[i];
		s->e = s->d;
		s->d = s->c;
		s->c = ROTLEFT(s->b, 30);
		s->b = s->a;
		s->a = s->t;
		i++;
	}
	while (i < 80)
	{
		s->t = ROTLEFT(s->a, 5) + (s->b ^ s->c ^ s->d) +
			s->e + ctx->k[3] + s->m[i];
		s->e = s->d;
		s->d = s->c;
		s->c = ROTLEFT(s->b, 30);
		s->b = s->a;
		s->a = s->t;
		i++;
	}
}
