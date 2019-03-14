/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 13:44:16 by zfaria            #+#    #+#             */
/*   Updated: 2019/03/14 15:18:18 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sha256.h>
#include <libft.h>

void	sha256_init(t_s256q *ctx)
{
	ctx->state[0] = 0x6a09e667;
	ctx->state[1] = 0xbb67ae85;
	ctx->state[2] = 0x3c6ef372;
	ctx->state[3] = 0xa54ff53a;
	ctx->state[4] = 0x510e527f;
	ctx->state[5] = 0x9b05688c;
	ctx->state[6] = 0x1f83d9ab;
	ctx->state[7] = 0x5be0cd19;
	ctx->datalen = 0;
	ctx->bitlen = 0;
	ft_bzero(ctx->data, 64);
}

void	sha256_update(t_s256q *ctx, uint8_t *msg, uint32_t len)
{
	uint32_t i;

	i = 0;
	while (i < len)
	{
		ctx->data[ctx->datalen] = msg[i];
		ctx->datalen++;
		if (ctx->datalen == 64)
		{
			sha256_transform(ctx, ctx->data);
			ctx->bitlen += 512;
			ctx->datalen = 0;
		}
		i++;
	}
}

void	sha256_transform(t_s256q *ctx, uint8_t *d)
{
	t_sql	s;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < 16)
	{
		s.m[i] = (d[j] << 24) | (d[j + 1] << 16) |
			(d[j + 2] << 8) | (d[j + 3]);
		j += 4;
		i++;
	}
	while (i < 64)
	{
		s.m[i] = S1(s.m[i - 2]) + s.m[i - 7] + S0(s.m[i - 15]) + s.m[i - 16];
		i++;
	}
	s.a = ctx->state[0];
	s.b = ctx->state[1];
	s.c = ctx->state[2];
	s.d = ctx->state[3];
	s.e = ctx->state[4];
	s.f = ctx->state[5];
	s.g = ctx->state[6];
	s.h = ctx->state[7];
	i = 0;
	while (i < 64)
	{
		s.t1 = s.h + EP1(s.e) + CH(s.e, s.f, s.g) + g_k[i] + s.m[i];
		s.t2 = EP0(s.a) + MAJ(s.a, s.b, s.c);
		s.h = s.g;
		s.g = s.f;
		s.f = s.e;
		s.e = s.d + s.t1;
		s.d = s.c;
		s.c = s.b;
		s.b = s.a;
		s.a = s.t1 + s.t2;
		i++;
	}
	ctx->state[0] += s.a;
	ctx->state[1] += s.b;
	ctx->state[2] += s.c;
	ctx->state[3] += s.d;
	ctx->state[4] += s.e;
	ctx->state[5] += s.f;
	ctx->state[6] += s.g;
	ctx->state[7] += s.h;
}

void	sha256_final(t_s256q *ctx, uint8_t *hash)
{
	uint32_t i;

	i = ctx->datalen;

	if (ctx->datalen < 56)
	{
		ctx->data[i++] = 0x80;
		while (i < 56)
			ctx->data[i++] = 0x00;
	}
	else
	{
		ctx->data[i++] = 0x80;
		while (i < 64)
			ctx->data[i++] = 0x00;
		sha256_transform(ctx, ctx->data);
		ft_memset(ctx->data, 0, 56);
	}
	ctx->bitlen += ctx->datalen * 8;
	ctx->data[63] = ctx->bitlen;
	ctx->data[62] = ctx->bitlen >> 8;
	ctx->data[61] = ctx->bitlen >> 16;
	ctx->data[60] = ctx->bitlen >> 24;
	ctx->data[59] = ctx->bitlen >> 32;
	ctx->data[58] = ctx->bitlen >> 40;
	ctx->data[57] = ctx->bitlen >> 48;
	ctx->data[56] = ctx->bitlen >> 56;
	sha256_transform(ctx, ctx->data);
	i = 0;
	while (i < 4)
	{
		hash[i] = (ctx->state[0] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 4] = (ctx->state[1] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 8] = (ctx->state[2] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 12] = (ctx->state[3] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 16] = (ctx->state[4] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 20] = (ctx->state[5] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 24] = (ctx->state[6] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 28] = (ctx->state[7] >> (24 - i * 8)) & 0x000000ff;
		i++;
	}
}
