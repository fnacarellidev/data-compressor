/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_encoded_string.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnacarel <fnacarel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 05:29:50 by fnacarel          #+#    #+#             */
/*   Updated: 2023/01/15 11:18:28 by fnacarel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./encoder.h"

/*
It will set an dictionary where the numeric representation of an letter will
store it's frequency in the data received
e.g: "foo baarr" (int)'f' = 102; [102] = (Huffman code of char f)
str[100] it's just an auxiliary str to build the encoded value of the char
*/
void	set_dict(t_min_heap_node *root, char **dict, char str[100], int top)
{
	if (root->left)
	{
		str[top] = '0';
		set_dict(root->left, dict, str, top + 1);
	}
	if (root->right)
	{
		str[top] = '1';
		set_dict(root->right, dict, str, top + 1);
	}
	if (is_leaf_node(root))
	{
		dict[(int)root->c] = calloc(sizeof(char *), top + 1);
		dict[(int)root->c] = strncpy(dict[(int)root->c], str, top);
	}
}

unsigned char	*get_encoded_string(char *str_to_encode, char **dict, int size)
{
	int				i;
	char			c;
	unsigned char	*encoded_str;
	char			**encoded_arr;
	int				total_len_of_strings;

	i = 0;
	total_len_of_strings = 0;
	encoded_arr = calloc(sizeof(char *), size);
	while (str_to_encode[i])
	{
		c = str_to_encode[i];
		encoded_arr[i] = strdup(dict[(int)c]);
		total_len_of_strings += strlen(encoded_arr[i]);
		i++;
	}
	encoded_str = calloc(sizeof(unsigned char), total_len_of_strings + 1);
	i = 0;
	while (i < size - 1)
	{
		strcat((char *)encoded_str, encoded_arr[i]);
		i++;
	}
	free_matr((void **)encoded_arr, size);
	return (encoded_str);
}
