/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_huffman_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnacarel <fnacarel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:43:06 by fnacarel          #+#    #+#             */
/*   Updated: 2023/01/14 20:21:23 by fnacarel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./std_dependencies.h"

t_min_heap_node	*get_huffman_tree(char *uniq_chars, int *freqs)
{
	int				i;
	t_min_heap_node	*top;
	t_min_heap_node	*left;
	t_min_heap_node	*right;
	t_min_heap		*huff_tree;
	t_min_heap_node	*final_node;

	huff_tree = get_min_heap_tree(uniq_chars, freqs);
	i = 0;
	while (!is_size_one(huff_tree))
	{
		left = extract_min_node(huff_tree);
		right = extract_min_node(huff_tree);
		top = new_node('$', left->freq + right->freq);
		top->left = left;
		top->right = right;
		insert_in_min_heap_tree(huff_tree, top);
		i++;
	}
	final_node = extract_min_node(huff_tree);
	free(huff_tree->array);
	free(huff_tree);
	return (final_node);
}
