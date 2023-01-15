/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unpack.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnacarel <fnacarel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 03:57:37 by fnacarel          #+#    #+#             */
/*   Updated: 2023/01/15 10:50:00 by fnacarel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./decoder.h"

/*
Checks if current bit is 1
*/
unsigned int	is_bit(unsigned char byte, int i)
{
    unsigned char	mask;

    mask = (1 << i);
    return (byte & mask);
}

void	prep_utils(FILE **file, unsigned char *byte, int *j, int *len, char *encoded_msg)
{
	*file = fopen("compact.fabin", "rb");
	*j = 0;
	*byte = 0;
	*len = strlen(encoded_msg);
}

/*
Decompress the file by analizing each bit at a time, everytime a bit 1 is found
walk to the right on the Huffman Tree, otherwise, walk left, do that until a
leaf_node is found, when a leaf_node is found, append it's symbol to the string
and do that until the end of the encoded string
*/
char	*unpack_message(t_min_heap_node **root, unsigned char *encoded_msg, int len_decoded)
{
	int				i;
	int				j;
	int				k;
	int				len;
	unsigned char	byte;
	FILE			*file;
	char			*decoded_msg;
	t_min_heap_node	*curr_node;

	k = 0;
	prep_utils(&file, &byte, &j, &len, (char *)encoded_msg);
	decoded_msg = calloc(sizeof(char), len_decoded + 1);
	if (!file)
	{
		printf("fopen failed\n");
		exit(1);
	}
	while (fread(&byte, sizeof(unsigned char), 1, file))
	{
		i = 7;
		while (i >= 0 && j < len)
		{
			if (is_bit(byte, i))
				curr_node = curr_node->right;
			else
				curr_node = curr_node->left;
			if (is_leaf_node(curr_node))
			{
				decoded_msg[k] = curr_node->c;
				curr_node = *root;
				k++;
			}
			j++;
			i--;
		}
	}
	decoded_msg[len_decoded] = '\0';
	fclose(file);
	return (decoded_msg);
}


/*
This function starts tracking how long the execution it's gonna take to finish
calls init_wrapper which grabs the info sent from encoder, then it decode and
decompress the message and then it sends the info to the encoder
*/
void	decode_and_unpack(t_wrap_info *wrapper)
{
	t_min_heap_node	*root;
	struct timeval	start;
	struct timeval	end;

	gettimeofday(&start, NULL);
	init_wrapper(wrapper);
	wrapper->decoded_msg = get_decoded_message(wrapper->uniq_chars, wrapper->freqs, wrapper->encoded_msg);
	root = get_huffman_tree(wrapper->uniq_chars, wrapper->freqs);
	wrapper->unpacked_msg = unpack_message(&root, wrapper->encoded_msg, strlen(wrapper->decoded_msg));
	free_tree(&root);
	detach_shm(wrapper->size, wrapper->freqs, wrapper->uniq_chars, wrapper->encoded_msg);
	gettimeofday(&end, NULL);
	wrapper->runtime = end.tv_usec - start.tv_usec;
	send_info_to_encoder(wrapper);
}
