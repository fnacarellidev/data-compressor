/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnacarel <fnacarel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:06:12 by fnacarel          #+#    #+#             */
/*   Updated: 2023/01/14 20:42:09 by fnacarel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./encoder.h"

void	free_matr(void **matr, int size)
{
	for (int i = 0; i < size; i++)
		free(matr[i]);
	free(matr);
}

void	free_stuff(char *uniq_chars, int *freq, char **dict, char *encoded_str)
{
	if (uniq_chars)
		free(uniq_chars);
	if (freq)
		free(freq);
	if (dict)
		free_matr((void **)dict, ASCII_LEN);
	if (encoded_str)
		free(encoded_str);
}
