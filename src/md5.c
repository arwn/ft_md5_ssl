/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 12:09:45 by awindham          #+#    #+#             */
/*   Updated: 2019/03/15 13:50:14 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <md5.h>
#include <libft.h>
#include <stdlib.h>

unsigned char g_padding[] =
{
	0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

void	md5_update(t_md5_ctx *context, uint8_t *input, uint32_t inputlen)
{
	unsigned int i;
	unsigned int index;
	unsigned int partlen;

	index = (context->count[0] >> 3) & 0x3F;
	partlen = 64 - index;
	context->count[0] += inputlen << 3;
	if (context->count[0] < (inputlen << 3))
		context->count[1]++;
	context->count[1] += inputlen >> 29;
	if (inputlen >= partlen)
	{
		ft_memcpy(&context->buffer[index], input, partlen);
		md5_transform(context->state, context->buffer);
		i = partlen;
		while (i + 64 <= inputlen)
		{
			md5_transform(context->state, &input[i]);
			i += 64;
		}
		index = 0;
	}
	else
		i = 0;
	ft_memcpy(&context->buffer[index], &input[i], inputlen - i);
}

void	md5_final(t_md5_ctx *context, uint8_t digest[16])
{
	unsigned int	index;
	unsigned int	padlen;
	unsigned char	bits[8];

	index = (context->count[0] >> 3) & 0x3F;
	padlen = (index < 56) ? (56 - index) : (120 - index);
	md5_encode(bits, context->count, 8);
	md5_update(context, g_padding, padlen);
	md5_update(context, bits, 8);
	md5_encode(digest, context->state, 16);
}

void	md5_encode(uint8_t *output, uint32_t *input, uint32_t len)
{
	unsigned int i;
	unsigned int j;

	i = 0;
	j = 0;
	while (j < len)
	{
		output[j] = input[i] & 0xFF;
		output[j + 1] = (input[i] >> 8) & 0xFF;
		output[j + 2] = (input[i] >> 16) & 0xFF;
		output[j + 3] = (input[i] >> 24) & 0xFF;
		i++;
		j += 4;
	}
}

void	md5_decode(uint32_t *output, uint8_t *input, unsigned int len)
{
	unsigned int i;
	unsigned int j;

	i = 0;
	j = 0;
	while (j < len)
	{
		output[i] = (input[j]) |
			(input[j + 1] << 8) |
			(input[j + 2] << 16) |
			(input[j + 3] << 24);
		i++;
		j += 4;
	}
}

void	md5_transform(uint32_t state[4], uint8_t block[64])
{
	unsigned int a;
	unsigned int b;
	unsigned int c;
	unsigned int d;
	unsigned int x[64];

	a = state[0];
	b = state[1];
	c = state[2];
	d = state[3];
	md5_decode(x, block, 64);
	FUN;
	state[0] += a;
	state[1] += b;
	state[2] += c;
	state[3] += d;
}
