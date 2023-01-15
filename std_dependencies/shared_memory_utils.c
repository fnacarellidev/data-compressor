/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_memory_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnacarel <fnacarel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:07:55 by fnacarel          #+#    #+#             */
/*   Updated: 2023/01/14 20:39:48 by fnacarel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./std_dependencies.h"

static int	get_shared_block(char *filename, int size, int key_val)
{
	key_t	key;
	int		shmid;

	key = ftok(filename, key_val);
	if (key == -1)
	{
		printf("Key failed.\n");
		exit(1);
	}
	shmid = shmget(key, size, 0644 | IPC_CREAT);
	return (shmid);
}

void	*attach_memory_block(char *filename, int size, int key_val)
{
	char	*result;
	int		shared_block_id;

	shared_block_id = get_shared_block(filename, size, key_val);
	if (shared_block_id == -1)
	{
		printf("shmget failed.\n");
		exit(1);
	}
	result = shmat(shared_block_id, NULL, 0);
	if (result == (char *)-1)
	{
		printf("shmat failed.\n");
		exit(1);
	}
	return (result);
}
