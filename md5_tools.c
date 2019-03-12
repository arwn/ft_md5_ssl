/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 14:12:01 by zfaria            #+#    #+#             */
/*   Updated: 2019/03/12 14:17:15 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>
#include <libft.h>
#include <md5.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define MD5_SIZE 16
#define BUFF_SIZE 64

int			die(int i)
{
	if (i == -1)
	{
		perror("open");
		return (-1);
	}
	else
	{
		perror("read");
		close(i);
		return (-1);
	}
}

int			compute_string_md5(
uint8_t *dest_str,
uint32_t dest_len,
char *md5_str)
{
	int				i;
	unsigned char	md5_value[MD5_SIZE];
	t_md5_ctx		md5;

	md5_init(&md5);
	md5_update(&md5, dest_str, dest_len);
	md5_final(&md5, md5_value);
	i = -1;
	while (++i < MD5_SIZE)
		md5_str = ft_strcat(md5_str, to_hex(md5_value[i]));
	return (0);
}

int			compute_file_md5(const char *file_path, char *md5_str, int i)
{
	int				fd;
	int				ret;
	unsigned char	data[BUFF_SIZE];
	unsigned char	md5_value[MD5_SIZE];
	t_md5_ctx		md5;

	fd = open(file_path, O_RDONLY);
	if (-1 == fd)
		return(die(fd));
	md5_init(&md5);
	while (1)
	{
		ret = read(fd, data, BUFF_SIZE);
		if (-1 == ret)
			return(die(fd));
		md5_update(&md5, data, ret);
		if (0 == ret || ret < BUFF_SIZE)
			break ;
	}
	close(fd);
	md5_final(&md5, md5_value);
	while (++i < MD5_SIZE)
		md5_str = ft_strcat(md5_str, to_hex(md5_value[i]));
	return (0);
}
