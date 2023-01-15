/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_dependencies.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnacarel <fnacarel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 20:06:34 by fnacarel          #+#    #+#             */
/*   Updated: 2023/01/14 20:37:12 by fnacarel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef STD_DEPENDENCIES_H
# define STD_DEPENDENCIES_H
# define ASCII_LEN 256
# define SEM_PROD "/tmpencoder"
# define SEM_CONS "/tmpdecoder"
# define FILENAME ".tmp"
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/ipc.h>
# include <sys/shm.h>
# include <sys/types.h>
# include <semaphore.h>

typedef struct s_min_heap_node
{
	char					c;
	unsigned int			freq;
	struct s_min_heap_node	*left;
	struct s_min_heap_node	*right;
}	t_min_heap_node;

typedef struct s_min_heap
{
	int	size;
	int	capacity;
	t_min_heap_node	**array;
}	t_min_heap;

void    			free_tree(t_min_heap_node **tree);
bool				is_size_one(t_min_heap *min_heap);
t_min_heap_node		*extract_min_node(t_min_heap *tree);
bool				is_leaf_node(t_min_heap_node *root);
t_min_heap_node		*new_node(char c, unsigned int freq);
t_min_heap_node		*get_huffman_tree(char *uniq_chars, int *freqs);
t_min_heap			*get_min_heap_tree(char *uniq_chars, int *freq);
void				close_semaphores(sem_t *consumer, sem_t *producer);
void				*attach_memory_block(char *filename, int size, int keyval);
void				insert_in_min_heap_tree(t_min_heap *tree, t_min_heap_node *node);
void				init_semaphores(sem_t **sem_cons, sem_t **sem_prod, int decoder_called);

#endif
