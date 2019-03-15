/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha1_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 11:44:55 by zfaria            #+#    #+#             */
/*   Updated: 2019/03/15 12:11:47 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <sha1.h>
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

int			compute_string_sha1(uint8_t *str, uint32_t len, char *res)
{
	t_s1ctx		ctx;
	uint8_t		hash[20];
	uint32_t	i;

	sha1_init(&ctx);
	sha1_update(&ctx, str, len);
	sha1_final(&ctx, hash);
	i = 0;
	ft_bzero(res, 64);
	while (i < 20)
		ft_fstrcat(res, to_hex(hash[i++]));
	return (0);
}

int			compute_file_sha1(char *file, char *res, char **buff)
{
	t_s1ctx	ctx;
	int		fd;
	char	buf[64];
	int		bread;
	uint8_t	hash[20];

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (die(fd, file));
	sha1_init(&ctx);
	if (read(fd, buf, 0) == -1)
		return (die(fd, file));
	ft_strclr(buf);
	while ((bread = read(fd, buf, 64)) > 0)
	{
		*buff = ft_fstrjoin(*buff, (char *)buf, 1);
		sha1_update(&ctx, (uint8_t *)buf, bread);
		ft_strclr(buf);
	}
	sha1_final(&ctx, hash);
	close(fd);
	bread = 0;
	while (bread < 20)
		ft_fstrcat(res, to_hex(hash[bread++]));
	return (0);
}
