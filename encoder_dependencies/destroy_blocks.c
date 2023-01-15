/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_blocks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnacarel <fnacarel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 20:39:58 by fnacarel          #+#    #+#             */
/*   Updated: 2023/01/15 11:08:43 by fnacarel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./encoder.h"

/*
Destroy every block I create using shmget
*/
void	destroy_blocks(void)
{
	key_t	key[8];
	int		shmid[8];

	for (int i = 0; i < 8; i++)
		key[i] = ftok(FILENAME, i);
	for (int i = 0; i < 8; i++)
		shmid[i] = shmget(key[i], 1, 0);
	for (int i = 0; i < 8; i++)
	{
		if (shmid[i] != -1)
			shmctl(shmid[i], IPC_RMID, NULL);
	}
}
