/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encoder.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnacarel <fnacarel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 19:41:14 by fnacarel          #+#    #+#             */
/*   Updated: 2023/01/15 06:03:32 by fnacarel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef ENCODER_H
# define ENCODER_H
# ifndef STD_DEPENDENCIES_H
#  include "../std_dependencies/std_dependencies.h"
# endif

typedef struct s_huff_data
{
	char	*uniq_chars;
	int		*freqs;
}	t_huff_data;

typedef struct s_decoder_info
{
	char		*data;
	int			data_len;
	int			compressed_len;
	long int	decoder_runtime;
}	t_decoder_info;

void			destroy_blocks(void);
char			*chars_found_in_str(char *str);
void			free_matr(void **matr, int size);
int				number_of_occurrences(char c, char *std_data);
int				*set_frequencies(char *uniq_chars, char *std_data, size_t size);
void			send_infos_to_decoder(int *freqs, char *uniq_chars, unsigned char *encoded_str);
void			free_stuff(char *uniq_chars, int *freq, char **dict, char *encoded_str);
void			get_info(t_decoder_info *info);
void			set_dict(t_min_heap_node *root, char **dict, char str[100], int top);
unsigned char	*get_encoded_string(char *str_to_encode, char **dict, int size);
void			print_info(t_decoder_info *info);
char    		*merge_args(int argc, char **argv);
void			compact(unsigned char *encoded_str);

#endif
