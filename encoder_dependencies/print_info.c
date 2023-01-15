/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnacarel <fnacarel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 05:32:48 by fnacarel          #+#    #+#             */
/*   Updated: 2023/01/15 05:51:31 by fnacarel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./encoder.h"

void	print_info(t_decoder_info *info)
{
	printf("Data decompressed: %s\n", info->data);
	printf("Size of data decompressed: %d\n", info->data_len);
	printf("Compressed data size: %d\n", info->compressed_len);
	printf("Runtime (μs): %lu\n", info->decoder_runtime);
}
