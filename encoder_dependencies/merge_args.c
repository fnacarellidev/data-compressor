/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnacarel <fnacarel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 05:35:03 by fnacarel          #+#    #+#             */
/*   Updated: 2023/01/15 11:21:16 by fnacarel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./encoder.h"

/*
Create an string which is the combination of every argv (except 0) combined,
no spaces are put in between.
*/
char    *merge_args(int argc, char **argv)
{
	int        i;
	int        j;
	int        k;
	char    *str;

	i = 1;
	j = 0;
	k = 0;
	while (i < argc)
		j += strlen(argv[i++]);
	str = calloc(sizeof(char), j + 1);
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
			str[k++] = argv[i][j++];
		i++;
	}
	return (str);
}
