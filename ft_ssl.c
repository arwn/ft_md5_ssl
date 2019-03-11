/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 13:08:49 by zfaria            #+#    #+#             */
/*   Updated: 2019/03/11 11:44:23 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <md5.h>
#include <ft_ssl.h>
#include <stdlib.h>
#include <string.h>
#include <libft.h>

const char *g_usage = "usage: ft_ssl command [opts] [args]";

int		g_quiet;
int		g_string;
char	*g_strings;
int		g_command;
char	*g_commands;

void	parse_flags(int argc, char **argv)
{
	while (ft_getopt(argc, argv, "qs:c:") != -1)
	{
		if (g_optopt == 'q')
			g_quiet = 1;
		if (g_optopt == 's')
		{
			g_string = 1;
			g_strings = g_optarg;
		}
		if (g_optopt == 'c')
		{
			g_command = 1;
			g_commands = g_optarg;
		}
	}
}

int main(int argc, char **argv) {
    char *msg;
    size_t len;
    int i;
    uint8_t result[16];
 
    if (argc < 2) {
        ft_printf("%s\n", g_usage);
        return 1;
    }
	parse_flags(argc - 1, argv + 1);
	if (g_string)
		msg = g_strings;
    len = ft_strlen(msg);
    md5((uint8_t*)msg, len, result);
    for (i = 0; i < 16; i++)
        ft_printf("%s", to_hex(result[i]));
    ft_printf("\n");
 
    return 0;
}
