/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_tools.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfaria <zfaria@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:50:08 by zfaria            #+#    #+#             */
/*   Updated: 2019/03/14 15:06:57 by zfaria           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA256_TOOLS_H
# define SHA256_TOOLS_H

int	compute_string_sha256(uint8_t *str, uint32_t len, char *res);

int	compute_file_sha256(char *file, char *res);

#endif
