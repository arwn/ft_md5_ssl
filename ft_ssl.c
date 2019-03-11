/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 13:08:49 by zfaria            #+#    #+#             */
/*   Updated: 2019/03/11 09:58:04 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <md5.h>
#include <ft_ssl.h>
#include <stdlib.h>
#include <string.h>

const char *g_usage = "usage: ft_ssl command [opts] [args]";

int main(int argc, char **argv) {
    char *msg;
    size_t len;
    int i;
    uint8_t result[16];
 
    if (argc < 2) {
        printf("usage: %s 'string'\n", argv[0]);
        return 1;
    }
    msg = argv[1];
 
    len = strlen(msg);
 
    md5((uint8_t*)msg, len, result);
    for (i = 0; i < 16; i++)
        printf("%s", to_hex(result[i]));
    puts("");
 
    return 0;
}
