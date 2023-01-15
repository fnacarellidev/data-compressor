/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnacarel <fnacarel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 02:29:39 by fnacarel          #+#    #+#             */
/*   Updated: 2023/01/15 10:54:51 by fnacarel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./decoder.h"

static void	send_decompressed_data(t_wrap_info *wrapper)
{
	int		size;
	char	*block;
	
	size = strlen(wrapper->unpacked_msg) + 1;
	block = attach_memory_block(FILENAME, size, 6);
	memcpy(block, wrapper->unpacked_msg, size);
}

static void	send_decompressed_data_bytes(t_wrap_info *wrapper)
{
	int		len;
	int		*block;

	len = strlen(wrapper->unpacked_msg);
	block = attach_memory_block(FILENAME, sizeof(int), 5);
	block[0] = len;
}

static void	send_compressed_data_bytes(void)
{
	int		fd;
	int		size;
	char	buf[1];
	int		*block;

	size = 0;
	fd = open("compact.fabin", O_RDONLY);
	while (read(fd, buf, 1))
		size++;
	block = attach_memory_block(FILENAME, size, 7);
	block[0] = size;
}

static void	send_runtime(t_wrap_info *wrapper)
{
	int	*block;

	block = attach_memory_block(FILENAME, sizeof(long int), 8);
	block[0] = wrapper->runtime;
}

void	send_info_to_encoder(t_wrap_info *wrapper)
{
	send_decompressed_data(wrapper);
	send_decompressed_data_bytes(wrapper);
	send_compressed_data_bytes();
	send_runtime(wrapper);
}
