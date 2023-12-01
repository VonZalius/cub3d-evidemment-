/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 20:12:46 by cmansey           #+#    #+#             */
/*   Updated: 2023/11/27 21:10:58 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Fonction pour créer une liste chaînée avec j éléments
t_element	*creer_liste(int j)
{
	t_element	*premier;
	t_element	*actuel;
	int			k;

	premier = malloc(sizeof(*premier));
	if (premier == NULL)
		exit(EXIT_FAILURE);
	premier->index = 1;
	actuel = premier;
	k = 2;
	while (k <= j)
	{
		actuel->suivant = malloc(sizeof(*premier));
		if (actuel->suivant == NULL)
			exit(EXIT_FAILURE);
		actuel = actuel->suivant;
		actuel->index = k;
		k++;
	}
	actuel->suivant = NULL;
	return (premier);
}

// Fonction pour libérer la mémoire allouée à la liste chaînée
void	liberer_liste(t_element *premier)
{
	t_element	*actuel;
	t_element	*suivant;

	actuel = premier;
	while (actuel != NULL)
	{
		suivant = actuel->suivant;
		free(actuel);
		actuel = suivant;
	}
}
