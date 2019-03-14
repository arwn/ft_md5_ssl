/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 13:19:46 by zfaria            #+#    #+#             */
/*   Updated: 2019/03/14 13:13:08 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <stdlib.h>

char	*to_hex(int num);
int		compute_file_md5(char *file_path, char *md5_str, int i);
int		compute_string_md5(uint8_t *ds, uint32_t dl, char *md5_str);

#endif
