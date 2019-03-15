/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doge.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awindham <awindham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 11:03:10 by awindham          #+#    #+#             */
/*   Updated: 2019/03/15 11:28:26 by awindham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const char *g_doge[16] = {
	"wow ",
	"such ",
	"very ",
	"fluff ",
	"bark ",
	"woof ",
	"doggo ",
	"so ",
	"such ",
	"amaze ",
	"much ",
	"cool ",
	"interest ",
	"fur ",
	"cute ",
	"hash "
};

char	*to_doge(char *hex)
{
	char	*done;
	int		i;

	done = malloc(strlen(hex) * 10);
	i = 0;
	while (*hex)
	{
		if (*hex >= 'a')
			strcat(&done[i], g_doge[*hex - 'a' + 10]);
		else if (*hex >= '0')
			strcat(&done[i], g_doge[*hex - '0']);
		i += strlen(g_doge[0]);
		hex++;
	}
	return (done);
}
