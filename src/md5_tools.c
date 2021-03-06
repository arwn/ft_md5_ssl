/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 14:12:01 by zfaria            #+#    #+#             */
/*   Updated: 2019/03/15 12:13:38 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>
#include <libft.h>
#include <md5.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define MD5_SIZE 16
#define BUFF_SIZE 64

int	die(int i, char *str)
{
	if (i == -1)
	{
		ft_printf("%s: %s: %s\n", "ft_ssl", str, strerror(errno));
		return (-1);
	}
	else
	{
		ft_printf("%s: %s: %s\n", "ft_ssl", str, strerror(errno));
		close(i);
		return (-1);
	}
}

int	md5_init(t_md5_ctx *context)
{
	context->count[0] = 0;
	context->count[1] = 0;
	context->state[0] = 0x67452301;
	context->state[1] = 0xEFCDAB89;
	context->state[2] = 0x98BADCFE;
	context->state[3] = 0x10325476;
	return (0);
}

int	compute_string_md5(uint8_t *dest_str, uint32_t dest_len, char *md5_str)
{
	int			i;
	uint8_t		md5_value[MD5_SIZE];
	t_md5_ctx	md5;

	md5_init(&md5);
	md5_update(&md5, dest_str, dest_len);
	md5_final(&md5, md5_value);
	i = -1;
	while (++i < MD5_SIZE)
		md5_str = ft_fstrcat(md5_str, to_hex(md5_value[i]));
	return (0);
}

int	compute_file_md5(char *file_path, char *md5_str, char **buff)
{
	int				fd;
	int				ret;
	unsigned char	data[BUFF_SIZE];
	unsigned char	md5_value[MD5_SIZE];
	t_md5_ctx		md5;

	fd = open(file_path, O_RDONLY);
	if (-1 == fd)
		return (die(fd, file_path));
	md5_init(&md5);
	ft_bzero(data, BUFF_SIZE);
	while ((ret = read(fd, data, BUFF_SIZE)) > 0)
	{
		*buff = ft_fstrjoin(*buff, (char *)data, 1);
		if (-1 == ret)
			return (die(fd, file_path));
		md5_update(&md5, data, ret);
		ft_bzero(data, BUFF_SIZE);
	}
	close(fd);
	md5_final(&md5, md5_value);
	fd = -1;
	while (++fd < MD5_SIZE)
		md5_str = ft_fstrcat(md5_str, to_hex(md5_value[fd]));
	return (0);
}
