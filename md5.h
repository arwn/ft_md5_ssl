/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awindham <awindham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 13:09:23 by zfaria            #+#    #+#             */
/*   Updated: 2019/03/08 16:43:34 by awindham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H

# include <stdlib.h>

typedef struct	s_context {
	uint8_t		*done;
	size_t		len;
	size_t		offset;
	uint32_t	a0;
	uint32_t	b0;
	uint32_t	c0;
	uint32_t	d0;
	uint32_t	w[16];
	uint32_t	tmp;
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
	uint32_t	i;
	uint32_t	f;
	uint32_t	g;
}				t_c;

void			md5(const uint8_t *initial_msg, size_t initial_len,
	uint8_t *digest);

#endif
