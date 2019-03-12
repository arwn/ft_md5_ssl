/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 09:43:20 by zfaria            #+#    #+#             */
/*   Updated: 2019/03/12 15:20:40 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

static char *g_ch = "0123456789abcdef";

uint8_t	*to_hex(int num)
{
	int			i;
	uint8_t		*res;

	res = ft_memalloc(3);
	i = 0;
	while (num > 0)
	{
		res[i] = g_ch[num % 16];
		num /= 16;
		i++;
	}
	if (i == 0)
	{
		res[0] = '0';
		res[1] = '0';
	}
	if (i == 1)
		res[0] = '0';
	ft_strrev(res);
	return (res);
}
