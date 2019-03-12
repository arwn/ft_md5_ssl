/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 12:53:41 by awindham          #+#    #+#             */
/*   Updated: 2019/03/12 14:07:18 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ft_ssl.h>
#include <libft.h>

#define MD5_SIZE		16
#define BUFF_SIZE 64
#define MD5_STR_LEN		(MD5_SIZE * 2)

#define PCR {perror("read"); close(fd); return (-1);}
#define PR {perror("open"); return (-1);}

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
		PR;
	md5_init(&md5);
	while (1)
	{
		ret = read(fd, data, BUFF_SIZE);
		if (-1 == ret)
			PCR;
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

int			main(int argc, char *argv[])
{
	int		ret;
	char	md5_str[MD5_STR_LEN + 1];

	(void)argc;
	(void)argv;
	ret = compute_file_md5(argv[1], md5_str, -1);
	ft_printf("[file - %s] md5 value: %s\n", argv[1], md5_str);
}
