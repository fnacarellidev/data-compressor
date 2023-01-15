/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_memory_ops.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnacarel <fnacarel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 01:01:52 by fnacarel          #+#    #+#             */
/*   Updated: 2023/01/15 10:40:28 by fnacarel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./decoder.h"

/*
Grabbing data that was sent from encoder, respectively
0 : Number of unique char in the data 
1 : Length of the encoded string
2 : Array of the frequencies of each character
3 : Array of the unique chars found in data
4 : The encoded message
*/
void	init_wrapper(t_wrap_info *wrapper)
{
	wrapper->size = attach_memory_block(FILENAME, sizeof(int), 0);
	wrapper->encoded_len = attach_memory_block(FILENAME, sizeof(int), 1);
	wrapper->freqs = attach_memory_block(FILENAME, *wrapper->size * sizeof(int), 2);
	wrapper->uniq_chars = attach_memory_block(FILENAME, *wrapper->size / sizeof(int), 3);
	wrapper->encoded_msg = attach_memory_block(FILENAME, *wrapper->encoded_len * sizeof(unsigned char), 4);
}

void	detach_shm(int *size, int *freqs, char *uniq_chars, unsigned char *encoded_msg)
{
	shmdt(size);
	shmdt(freqs);
	shmdt(uniq_chars);
	shmdt(encoded_msg);
}
