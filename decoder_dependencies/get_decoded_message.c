/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_decoded_message.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnacarel <fnacarel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:39:47 by fnacarel          #+#    #+#             */
/*   Updated: 2023/01/15 10:53:04 by fnacarel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./decoder.h"

static int	get_decoded_message_len(t_min_heap_node **root, unsigned char *encoded_msg);
static char	*init_decoded_msg(t_min_heap_node **root, unsigned char *encoded_msg, int size);

char	*get_decoded_message(char *uniq_chars, int *freqs, unsigned char *encoded_msg)
{
	int				decoded_len;
	char			*decoded_msg;
	t_min_heap_node	*root;

	root = get_huffman_tree(uniq_chars, freqs);
	decoded_len = get_decoded_message_len(&root, encoded_msg);
	decoded_msg = init_decoded_msg(&root, encoded_msg, decoded_len);
	free_tree(&root);
	return (decoded_msg);
}

/*
Decodes the encoded message
*/
static char	*init_decoded_msg(t_min_heap_node **root, unsigned char *encoded_msg, int size)
{
	int				i;
	int				j;
	char			*decoded_msg;
	t_min_heap_node	*curr_node;

	i = 0;
	j = 0;
	decoded_msg = calloc(sizeof(char), size + 1);
	while (encoded_msg[i])
	{
		curr_node = *root;
		while (!is_leaf_node(curr_node))
		{
			if (encoded_msg[i] == '0')
				curr_node = curr_node->left;
			else
				curr_node = curr_node->right;
			i++;
		}
		decoded_msg[j] = curr_node->c;
		j++;
	}
	decoded_msg[j] = '\0';
	return (decoded_msg);
}

static int	get_decoded_message_len(t_min_heap_node **root, unsigned char *encoded_msg)
{
	int				i;
	int				j;
	t_min_heap_node	*curr_node;

	i = 0;
	j = 0;
	while (encoded_msg[i])
	{
		curr_node = *root;
		while (!is_leaf_node(curr_node))
		{
			if (encoded_msg[i] == '0')
				curr_node = curr_node->left;
			else
				curr_node = curr_node->right;
			i++;
		}
		j++;
	}
	return (j);
}
