/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnacarel <fnacarel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 14:04:25 by fnacarel          #+#    #+#             */
/*   Updated: 2023/01/15 06:00:56 by fnacarel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./encoder.h"

static void		quit_program(t_decoder_info *info, sem_t *sem_cons, sem_t *sem_prod);
static void		init_data(t_huff_data *data, char ***dict, char *str_to_encode, t_min_heap_node **tree);

int	main(int argc, char **argv)
{
	t_huff_data		data;
	int				size;
	char			**dict;
	t_min_heap_node	*tree;
	sem_t			*sem_cons = NULL;
	sem_t			*sem_prod = NULL;
	unsigned char	*encoded_str;
	t_decoder_info	info;
	char			*str_to_encode;

	if (argc < 2 || strlen(argv[1]) == 0 || strlen(argv[1]) == 1)
	{
		printf("Please give me some data!\n");
		exit(1);
	}
	str_to_encode = merge_args(argc, argv);
	size = strlen(str_to_encode) + 1;
	init_data(&data, &dict, str_to_encode, &tree);
	init_semaphores(&sem_cons, &sem_prod, 0);
	encoded_str = get_encoded_string(str_to_encode, dict, size);
	compact(encoded_str);
	send_infos_to_decoder(data.freqs, data.uniq_chars, encoded_str);
	sem_post(sem_cons);
	free_stuff(data.uniq_chars, data.freqs, dict, (char *)encoded_str);
	free_tree(&tree);
	quit_program(&info, sem_cons, sem_prod);
	return (0);
}

static void	quit_program(t_decoder_info *info, sem_t *sem_cons, sem_t *sem_prod)
{
	sem_wait(sem_prod);
	get_info(info);
	print_info(info);
	close_semaphores(sem_cons, sem_prod);
	destroy_blocks();
}

static void	init_data(t_huff_data *data, char ***dict, char *str_to_encode, t_min_heap_node **tree)
{
	char	codify[100];

	data->uniq_chars = chars_found_in_str(str_to_encode);
	if (strlen(data->uniq_chars) == 1)
	{
		printf("Please give me at least 2 characters\n");
		free(data->uniq_chars);
		free(str_to_encode);
		exit(1);
	}
	*dict = calloc(sizeof(char *), 256);
	data->freqs = set_frequencies(data->uniq_chars, str_to_encode, strlen(data->uniq_chars));
	*tree = get_huffman_tree(data->uniq_chars, data->freqs);
	set_dict(*tree, *dict, codify, 0);
}
