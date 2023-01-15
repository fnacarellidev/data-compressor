/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_heap_implementation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnacarel <fnacarel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:16:30 by fnacarel          #+#    #+#             */
/*   Updated: 2023/01/15 10:58:21 by fnacarel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./std_dependencies.h"

static int	parent_index(int index)
{
	return ((index - 1) / 2);
}

static int	left_child(int index)
{
	return ((2 * index) + 1);
}

static int	right_child(int index)
{
	return ((2 * index) + 2);
}

bool	is_size_one(t_min_heap *min_heap)
{
	if (min_heap->size == 1)
		return (true);
	return (false);
}

bool	is_leaf_node(t_min_heap_node *root)
{
	if (root->right == NULL && root->left == NULL)
		return (true);
	return (false);
}

t_min_heap_node	*new_node(char c, unsigned int freq)
{
	t_min_heap_node	*new_node;

	new_node = (t_min_heap_node *) malloc(sizeof(t_min_heap_node));
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->c = c;
	new_node->freq = freq;
	return (new_node);
}

static void	swap_min_heap_node(t_min_heap_node **node_1, t_min_heap_node **node_2)
{
	t_min_heap_node	*temp;

	temp = *node_1;
	*node_1 = *node_2;
	*node_2 = temp;
}

/*
Heapify makes sure the min heap data structure keeps its properties such as
smallest element at the top of the tree.
*/
static void	heapify(t_min_heap *tree, int index)
{
	int	left;
	int	right;
	int	smallest;

	smallest = index;
	left = left_child(index);
	right = right_child(index);
	if (left < tree->size && \
			tree->array[left]->freq < tree->array[smallest]->freq)
		smallest = left;
	if (right < tree->size && \
			tree->array[right]->freq < tree->array[smallest]->freq)
		smallest = right;
	if (smallest != index)
	{
		swap_min_heap_node(&tree->array[smallest], &tree->array[index]);
		heapify(tree, smallest);
	}
}

static void	set_min_heap_tree(t_min_heap *tree)
{
	int		p;
	int		last_index;

	last_index = tree->size - 1;
	p = parent_index(last_index);
	while (p >= 0)
	{
		heapify(tree, p);
		p--;
	}
}

static t_min_heap	*init_min_heap(unsigned int capacity)
{
	t_min_heap	*new_min_heap;

	new_min_heap = (t_min_heap *) malloc(sizeof(t_min_heap));
	new_min_heap->size = 0;
	new_min_heap->capacity = capacity;
	new_min_heap->array = (t_min_heap_node **) malloc(sizeof(t_min_heap *) * new_min_heap->capacity);
	return (new_min_heap);
}

t_min_heap	*get_min_heap_tree(char *uniq_chars, int *freq)
{
	int			i;
	t_min_heap	*tree;
	int			nodes_qty;

	i = 0;
	nodes_qty = strlen(uniq_chars);
	tree = init_min_heap(nodes_qty);
	while (i < nodes_qty)
	{
		tree->array[i] = new_node(uniq_chars[i], freq[i]);
		i++;
	}
	tree->size = nodes_qty;
	set_min_heap_tree(tree);
	return (tree);
}

t_min_heap_node	*extract_min_node(t_min_heap *tree)
{
	int				last_index;
	t_min_heap_node	*node_extracted;

	last_index = tree->size - 1;
	node_extracted = tree->array[0];
	tree->array[0] = tree->array[last_index];
	--tree->size;
	heapify(tree, 0);
	return (node_extracted);
}

void	insert_in_min_heap_tree(t_min_heap *tree, t_min_heap_node *node)
{
	int	i;

	++tree->size;
	i = tree->size - 1;
	while (i != 0 && node->freq < tree->array[parent_index(i)]->freq)
	{
		tree->array[i] = tree->array[parent_index(i)];
		i = parent_index(i);
	}
	tree->array[i] = node;
}
