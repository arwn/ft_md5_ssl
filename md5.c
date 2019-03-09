/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awindham <awindham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 13:09:16 by zfaria            #+#    #+#             */
/*   Updated: 2019/03/08 16:51:42 by awindham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <md5.h>

#include <stdlib.h>
#include <stdio.h>
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

const uint32_t g_k[64] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

const uint32_t g_s[] =
{7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

#define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))

void		to_bytes(uint32_t val, uint8_t *bytes)
{
	bytes[0] = (uint8_t)val;
	bytes[1] = (uint8_t)(val >> 8);
	bytes[2] = (uint8_t)(val >> 16);
	bytes[3] = (uint8_t)(val >> 24);
}

uint32_t	to_int32(const uint8_t *bytes)
{
	return ((uint32_t)bytes[0]
	| ((uint32_t)bytes[1] << 8)
	| ((uint32_t)bytes[2] << 16)
	| ((uint32_t)bytes[3] << 24));
}

/*
** 	initial_len * 8 >> 32
*/

void		md5init(const uint8_t *initial_msg, size_t initial_len, t_c *q)
{
	q->a0 = 0x67452301;
	q->b0 = 0xefcdab89;
	q->c0 = 0x98badcfe;
	q->d0 = 0x10325476;
	q->len = initial_len + 1;
	while (q->len % (512 / 8) != 448 / 8)
		q->len++;
	q->done = (uint8_t*)malloc(q->len + 8);
	memcpy(q->done, initial_msg, initial_len);
	q->done[initial_len] = 0x80;
	q->offset = initial_len + 1;
	while (q->offset < q->len)
		q->done[q->offset++] = 0;
	to_bytes(initial_len * 8, q->done + q->len);
	to_bytes(initial_len >> 29, q->done + q->len + 4);
}

void		beef(t_c *q)
{
	int i;

	i = 0;
	while (i < 64)
	{
		if (i < 16)
		{
			q->f = (q->b & q->c) | ((~q->b) & q->d);
			q->g = i;
		}
		else if (i < 32)
		{
			q->f = (q->d & q->b) | ((~q->d) & q->c);
			q->g = (5 * i + 1) % 16;
		}
		else if (i < 48)
		{
			q->f = q->b ^ q->c ^ q->d;
			q->g = (3 * i + 5) % 16;
		}
		else
		{
			q->f = q->c ^ (q->b | (~q->d));
			q->g = (7 * i) % 16;
		}
		q->tmp = q->d;
		q->d = q->c;
		q->c = q->b;
		q->b = q->b + LEFTROTATE((q->a + q->f + g_k[i] + q->w[q->g]), g_s[i]);
		q->a = q->tmp;
		i++;
	}
}

void		md5(const uint8_t *initial_msg, size_t initial_len, uint8_t *digest)
{
	t_c q;
	int i;

	md5init(initial_msg, initial_len, &q);
	q.offset = 0;
	while (q.offset < q.len)
	{
		i = 0;
		while (i < 16)
		{
			q.w[i] = to_int32(q.done + q.offset + i * 4);
			i++;
		}
		q.a = q.a0;
		q.b = q.b0;
		q.c = q.c0;
		q.d = q.d0;
		beef(&q);
		q.a0 += q.a;
		q.b0 += q.b;
		q.c0 += q.c;
		q.d0 += q.d;
		q.offset += (512 / 8);
	}
	free(q.done);
	to_bytes(q.a0, digest);
	to_bytes(q.b0, digest + 4);
	to_bytes(q.c0, digest + 8);
	to_bytes(q.d0, digest + 12);
}
