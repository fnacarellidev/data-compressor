/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnacarel <fnacarel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 20:17:59 by fnacarel          #+#    #+#             */
/*   Updated: 2023/01/15 05:20:52 by fnacarel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./decoder.h"

void	gen_decompressed_file(t_wrap_info *wrapper)
{
	int	fd;
	int	size;

	size = strlen(wrapper->unpacked_msg);
	fd = open("decompressed.fabin", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	for (int i = 0; i < size; i++)
		write(fd, &(wrapper->unpacked_msg[i]), 1);
}

int	main(void)
{
	t_wrap_info		*wrapper;
	sem_t			*sem_cons;
	sem_t			*sem_prod;

	wrapper = calloc(sizeof(t_wrap_info), 1);
	init_semaphores(&sem_cons, &sem_prod, 1);
	sem_wait(sem_cons);
	decode_and_unpack(wrapper);
	gen_decompressed_file(wrapper);
	free(wrapper->decoded_msg);
	free(wrapper);
	sem_post(sem_prod);
	sem_close(sem_cons);
	sem_close(sem_prod);
	return (0);
}
