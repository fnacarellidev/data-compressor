/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decoder.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnacarel <fnacarel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 20:12:41 by fnacarel          #+#    #+#             */
/*   Updated: 2023/01/15 10:55:24 by fnacarel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef DECODER_H
# define DECODER_H
# ifndef STD_DEPENDENCIES_H
#  include "../std_dependencies/std_dependencies.h"
# endif
# include <sys/time.h>

typedef struct s_wrap_info
{
	int				*size;
	int				*freqs;
	char			*uniq_chars;
	char			*decoded_msg;
	char			*unpacked_msg;
	int				*encoded_len;
	unsigned char	*encoded_msg;
	long int		runtime;
}	t_wrap_info;

char	*get_decoded_message(char *uniq_chars, int *freqs, unsigned char *encoded_msg);
void	send_info_to_encoder(t_wrap_info *wrapper);
void	init_wrapper(t_wrap_info *wrapper);
void	detach_shm(int *size, int *freqs, char *uniq_chars, unsigned char *encoded_msg);
void	decode_and_unpack(t_wrap_info *wrapper);

#endif
