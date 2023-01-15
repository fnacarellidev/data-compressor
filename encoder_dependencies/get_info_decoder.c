/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info_decoder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnacarel <fnacarel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 02:44:43 by fnacarel          #+#    #+#             */
/*   Updated: 2023/01/15 02:56:48 by fnacarel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./encoder.h"
#include <string.h>

void	get_decompressed_data_bytes(t_decoder_info *info)
{
	int	*block;

	block = attach_memory_block(FILENAME, sizeof(int), 5);
	info->data_len = block[0];
}

void	get_decompressed_data(t_decoder_info *info)
{
	int		size;
	char	*block;

	size = info->data_len + 1;
	info->data = calloc(sizeof(char), size);
	block = attach_memory_block(FILENAME, size, 6);
	memcpy(info->data, block, size);
}

void	get_compressed_data_bytes(t_decoder_info *info)
{
	int	*block;

	block = attach_memory_block(FILENAME, sizeof(int), 7);
	info->compressed_len = block[0];
}

void	get_runtime(t_decoder_info *info)
{
	long int	*block;

	block = attach_memory_block(FILENAME, sizeof(long int), 8);
	info->decoder_runtime = block[0];
}


void	get_info(t_decoder_info *info)
{
	get_decompressed_data_bytes(info);
	get_decompressed_data(info);
	get_compressed_data_bytes(info);
	get_runtime(info);
}
