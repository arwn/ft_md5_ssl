/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 11:16:40 by zfaria            #+#    #+#             */
/*   Updated: 2019/03/15 12:08:35 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sha1.h>
#include <libft.h>

void	sha1_transform(t_s1ctx *ctx, uint8_t *data)
{
	uint64_t	i;
	uint64_t	j;
	t_sql		s;

	i = 0;
	j = 0;
	sha1_transform_1(ctx, data, &s);
	sha1_transform_2(ctx, &s);
	sha1_transform_3(ctx, &s);
	ctx->state[0] += s.a;
	ctx->state[1] += s.b;
	ctx->state[2] += s.c;
	ctx->state[3] += s.d;
	ctx->state[4] += s.e;
}

void	sha1_init(t_s1ctx *ctx)
{
	ctx->datalen = 0;
	ctx->bitlen = 0;
	ctx->state[0] = 0x67452301;
	ctx->state[1] = 0xEFCDAB89;
	ctx->state[2] = 0x98BADCFE;
	ctx->state[3] = 0x10325476;
	ctx->state[4] = 0xc3d2e1f0;
	ctx->k[0] = 0x5a827999;
	ctx->k[1] = 0x6ed9eba1;
	ctx->k[2] = 0x8f1bbcdc;
	ctx->k[3] = 0xca62c1d6;
}

void	sha1_update(t_s1ctx *ctx, uint8_t *data, uint64_t len)
{
	uint64_t i;

	i = 0;
	while (i < len)
	{
		ctx->data[ctx->datalen] = data[i];
		ctx->datalen++;
		if (ctx->datalen == 64)
		{
			sha1_transform(ctx, ctx->data);
			ctx->bitlen += 512;
			ctx->datalen = 0;
		}
		i++;
	}
}

void	sha1_finale(t_s1ctx *ctx)
{
	int i;

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
		sha1_transform(ctx, ctx->data);
		ft_memset(ctx->data, 0, 56);
	}
}

void	sha1_final(t_s1ctx *ctx, uint8_t *hash)
{
	int i;

	sha1_finale(ctx);
	ctx->bitlen += ctx->datalen * 8;
	ctx->data[63] = ctx->bitlen;
	ctx->data[62] = ctx->bitlen >> 8;
	ctx->data[61] = ctx->bitlen >> 16;
	ctx->data[60] = ctx->bitlen >> 24;
	ctx->data[59] = ctx->bitlen >> 32;
	ctx->data[58] = ctx->bitlen >> 40;
	ctx->data[57] = ctx->bitlen >> 48;
	ctx->data[56] = ctx->bitlen >> 56;
	sha1_transform(ctx, ctx->data);
	i = 0;
	while (i < 4)
	{
		hash[i] = (ctx->state[0] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 4] = (ctx->state[1] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 8] = (ctx->state[2] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 12] = (ctx->state[3] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 16] = (ctx->state[4] >> (24 - i * 8)) & 0x000000ff;
		i++;
	}
}
