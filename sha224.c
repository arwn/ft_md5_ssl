/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 13:44:16 by zfaria            #+#    #+#             */
/*   Updated: 2019/03/15 10:43:57 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sha224.h>
#include <libft.h>

void	sha224_init(t_s256q *ctx)
{
	ctx->state[0] = 0xc1059ed8;
	ctx->state[1] = 0x367cd507;
	ctx->state[2] = 0x3070dd17;
	ctx->state[3] = 0xf70e5939;
	ctx->state[4] = 0xffc00b31;
	ctx->state[5] = 0x68581511;
	ctx->state[6] = 0x64f98fa7;
	ctx->state[7] = 0xbefa4fa4;
	ctx->datalen = 0;
	ctx->bitlen = 0;
	ft_bzero(ctx->data, 64);
}

void	sha224_update(t_s256q *ctx, uint8_t *msg, uint32_t len)
{
	uint32_t i;

	i = 0;
	while (i < len)
	{
		ctx->data[ctx->datalen] = msg[i];
		ctx->datalen++;
		if (ctx->datalen == 64)
		{
			sha224_transform(ctx, ctx->data);
			ctx->bitlen += 512;
			ctx->datalen = 0;
		}
		i++;
	}
}

void	sha224_final(t_s256q *ctx, uint8_t *hash)
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
		sha224_transform(ctx, ctx->data);
		ft_memset(ctx->data, 0, 56);
	}
	sha224_finale(ctx, hash);
}

void	sha224_finale(t_s256q *ctx, uint8_t *hash)
{
	int i;

	ctx->bitlen += ctx->datalen * 8;
	ctx->data[63] = ctx->bitlen;
	ctx->data[62] = ctx->bitlen >> 8;
	ctx->data[61] = ctx->bitlen >> 16;
	ctx->data[60] = ctx->bitlen >> 24;
	ctx->data[59] = ctx->bitlen >> 32;
	ctx->data[58] = ctx->bitlen >> 40;
	ctx->data[57] = ctx->bitlen >> 48;
	ctx->data[56] = ctx->bitlen >> 56;
	sha224_transform(ctx, ctx->data);
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
		i++;
	}
}
