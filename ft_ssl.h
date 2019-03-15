/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awindham <awindham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 13:19:46 by zfaria            #+#    #+#             */
/*   Updated: 2019/03/15 11:22:34 by awindham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <stdlib.h>

char	*to_hex(int num);
int		compute_string_md5(uint8_t *ds, uint32_t dl, char *md5_str);
int		compute_file_md5(char *file_path, char *md5_str, char **buf);

int		compute_string_sha256(uint8_t *str, uint32_t len, char *res);
int		compute_file_sha256(char *file, char *res, char **buf);

char	*to_doge(char *hex);

#endif
