/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnacarel <fnacarel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 20:20:03 by fnacarel          #+#    #+#             */
/*   Updated: 2023/01/14 20:20:12 by fnacarel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./std_dependencies.h"

void	free_tree(t_min_heap_node **tree)
{
    if (*tree == NULL)
        return ;
    free_tree(&(*tree)->left);
    free_tree(&(*tree)->right);
    (*tree)->right = NULL;
    (*tree)->left = NULL;
    free(*tree);
    *tree = NULL;
}
