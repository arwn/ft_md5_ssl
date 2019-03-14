/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:50:05 by zfaria            #+#    #+#             */
/*   Updated: 2019/03/14 15:17:56 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <sha256.h>
#include <ft_ssl.h>
#include <unistd.h>
#include <fcntl.h>

static int	die(int i, char *str)
{
	if (i == -1)
	{
		perror("open");
		return (-1);
	}
	else
	{
		ft_putstr("ft_ssl: ");
		perror(str);
		close(i);
		return (-1);
	}
}

int			compute_string_sha256(uint8_t *str, uint32_t len, char *res)
{
	t_s256q		ctx;
	uint8_t		hash[32];
	uint32_t	i;

	sha256_init(&ctx);
	sha256_update(&ctx, str, len);
	sha256_final(&ctx, hash);
	i = 0;
	ft_bzero(res, 64);
	while (i < 32)
		ft_strcat(res, to_hex(hash[i++]));
	return (0);
}

int			compute_file_sha256(char *file, char *res)
{
	t_s256q	ctx;
	int		fd;
	char	buf[64];
	int		bread;
	uint8_t	hash[32];

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (die(fd, file));
	sha256_init(&ctx);
	if (read(fd, buf, 0) == -1)
		return (die(fd, file));
	ft_strclr(buf);
	while ((bread = read(fd, buf, 64)) > 0)
	{
		sha256_update(&ctx, (uint8_t *)buf, bread);
		ft_strclr(buf);
	}
	sha256_final(&ctx, hash);
	close(fd);
	bread = 0;
	while (bread < 32)
		ft_strcat(res, to_hex(hash[bread++]));
	return (0);
}
