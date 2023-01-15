/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compact_huff_code.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */ 
/*   By: fnacarel <fnacarel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 01:28:03 by fnacarel          #+#    #+#             */
/*   Updated: 2023/01/15 11:07:28 by fnacarel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./encoder.h"

/*
This function compacts the Huffman Code, it takes every 8 chars in the Huffman
code and write it as bits in one char and then write this byte to the file
*/
void	write_to_compact(FILE *file, unsigned char *encoded_str)
{
	int				i;
	int				j;
	unsigned char	byte;
	unsigned char	mask;

	i = 0;
	j = 7;
	byte = 0;
	while (encoded_str[i])
	{
		mask = 1;
		if (encoded_str[i] == '1')
		{
			mask = mask << j;
			byte = byte | mask;
		}
		j--;
		if (j < 0)
		{
			fwrite(&byte, sizeof(unsigned char), 1, file);
			byte = 0;
			j = 7;
		}
		i++;
	}
	if (j != 7)
		fwrite(&byte, sizeof(unsigned char), 1, file);
}

void	compact(unsigned char *encoded_str)
{
	FILE			*file;

	file = fopen("compact.fabin", "wb");
	if (!file)
	{
		printf("Failed to open/create file\n");
		exit(1);
	}
	write_to_compact(file, encoded_str);
	fclose(file);
}
