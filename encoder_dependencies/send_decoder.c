/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_decoder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnacarel <fnacarel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:56:38 by fnacarel          #+#    #+#             */
/*   Updated: 2023/01/15 12:14:46 by fnacarel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./encoder.h"

static void	send_freqs_to_decoder(int *freqs, int size)
{
	int	*block;

	block = attach_memory_block(FILENAME, sizeof(int) * size, 2);
	for (int i = 0; i < size; i++)
		block[i] = freqs[i];
	shmdt(block);
}

static void	send_freq_size_to_decoder(int size)
{
	int	*block;

	block = attach_memory_block(FILENAME, sizeof(int), 0);
	block[0] = size;
	shmdt(block);
}

static void	send_uniq_chars_to_decoder(char *uniq_chars)
{
	int		size;
	char	*block;

	size = strlen(uniq_chars) + 1;
	block = attach_memory_block(FILENAME, size, 3);
	memcpy(block, uniq_chars, size);
	shmdt(block);
}

static void	send_encoded_str_to_decoder(unsigned char *encoded_str)
{
	int				size;
	unsigned char	*block;

	size = strlen((char *)encoded_str) + 1;
	block = attach_memory_block(FILENAME, size, 4);
	memcpy(block, encoded_str, size);
	shmdt(block);
}

static void	send_encoded_len(unsigned char *encoded_str)
{
	int	size;
	int	*block;

	size = strlen((char *)encoded_str) + 1;
	block = attach_memory_block(FILENAME, sizeof(int), 1);
	block[0] = size;
	shmdt(block);
}

void	send_infos_to_decoder(int *freqs, char *uniq_chars, unsigned char *encoded_str)
{
	send_freq_size_to_decoder(strlen(uniq_chars));
	send_encoded_len(encoded_str);
	send_freqs_to_decoder(freqs, strlen(uniq_chars));
	send_uniq_chars_to_decoder(uniq_chars);
	send_encoded_str_to_decoder(encoded_str);
}
