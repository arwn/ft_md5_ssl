/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 12:53:41 by awindham          #+#    #+#             */
/*   Updated: 2019/03/14 16:10:42 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"
#include "sha256.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ft_ssl.h>
#include <libft.h>

int		g_r = 0;
int		g_q = 0;
int		g_s = 0;
int		g_p = 0;
char	*g_buff;
char	*g_alg;

void	print_str(char *str, char *src)
{
	if (g_q || src == 0)
	{
		ft_printf("%s\n", str);
	}
	else if (g_r)
	{
		if (g_optopt == 's')
			ft_printf("%s \"%s\"\n", str, src);
		else
			ft_printf("%s %s\n", str, src);
	}
	else
	{
		if (g_optopt == 's')
			ft_printf("%s(\"%s\")= %s\n", g_alg, src, str);
		else
			ft_printf("%s(%s)= %s\n", g_alg, src, str);
	}
}

void	parse_opts(int argc, char **argv, int (*file)(char *, char *, char **),
	int (*string)(uint8_t *str, uint32_t len, char *))
{
	char	str[65];

	ft_bzero(str, 65);
	while (ft_getopt(argc - 1, argv + 1, "pqrs:") != -1)
	{
		if (g_optopt == 'q')
			g_q = 1;
		if (g_optopt == 'r')
			g_r = 1;
		if (g_optopt == 'p')
		{
			file("/dev/fd/0", str, &g_buff);
			ft_printf(g_buff);
			print_str(str, 0);
		}
		if (g_optopt == 's')
		{
			g_s = 1;
			string((uint8_t*)g_optarg, ft_strlen(g_optarg), str);
			print_str(str, g_optarg);
		}
		ft_bzero(str, 65);
	}
}

void	parse_args(int argc, char **argv, int (*file)(char *, char *, char **),
	int (*string)(uint8_t *str, uint32_t len, char *))
{
	int		i;
	char	str[65];

	ft_bzero(str, 65);
	parse_opts(argc, argv, file, string);
	i = g_optind;
	g_optopt = 0;
	if (argc - 1 == i)
	{
		file("/dev/fd/0", str, &g_buff);
		ft_printf(g_buff);
		print_str(str, 0);
	}
	while (++i < argc)
	{
		if (file(argv[i], str, &g_buff) == 0)
			print_str(str, argv[i]);
		ft_strclr(str);
	}
}

int		main(int argc, char **argv)
{
	char *usage;

	g_buff = ft_strnew(64);
	usage = "usage: ft_ssl [md5|sha256] [opts] [args]\n";
	if (argc < 2)
		ft_printf("%s", usage);
	else
	{
		if (ft_strequ(argv[1], "md5"))
		{
			g_alg = "MD5";
			parse_args(argc, argv, compute_file_md5, compute_string_md5);
		}
		else if (ft_strequ(argv[1], "sha256"))
		{
			g_alg = "SHA256";
			parse_args(argc, argv, compute_file_sha256, compute_string_sha256);
		}
		else
		{
			ft_printf("%s", usage);
		}
	}
	free(g_buff);
}
