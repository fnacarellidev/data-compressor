/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnacarel <fnacarel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 20:33:23 by fnacarel          #+#    #+#             */
/*   Updated: 2023/01/14 20:22:35 by fnacarel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./std_dependencies.h"

void	init_semaphores(sem_t **sem_cons, sem_t **sem_prod, int decoder_called)
{
	if (decoder_called)
	{
		*sem_prod = sem_open(SEM_PROD, 0);
		*sem_cons = sem_open(SEM_CONS, 1);
	}
	else
	{
		*sem_prod = sem_open(SEM_PROD, O_CREAT, 0660, 0);
		*sem_cons = sem_open(SEM_CONS, O_CREAT, 0660, 1);
	}
	if (*sem_cons == SEM_FAILED)
	{
		perror("sem_open/consumer");
		exit(1);
	}
	if (*sem_prod == SEM_FAILED)
	{
		perror("sem_open/producer");
		exit(1);
	}
}

void	close_semaphores(sem_t *consumer, sem_t *producer)
{
	sem_unlink(SEM_CONS);
	sem_unlink(SEM_PROD);
	sem_close(consumer);
	sem_close(producer);
}
