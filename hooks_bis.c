/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:04:31 by cmansey           #+#    #+#             */
/*   Updated: 2023/11/28 00:38:53 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	map_key_to_index(int keycode)
{
	switch (keycode)
	{
		case 65307: return KEY_ESC; // Exemple: KEY_ESC pourrait être 1
		case 65361: return KEY_LEFT; // Exemple: KEY_LEFT pourrait être 2
		case 65363: return KEY_RIGHT; // Exemple: KEY_RIGHT pourrait être 3
		case 119: return KEY_W; // Exemple: KEY_W pourrait être 4
		case 97: return KEY_A; // Exemple: KEY_A pourrait être 5
		case 115: return KEY_S; // Exemple: KEY_S pourrait être 6
		case 100: return KEY_D; // Exemple: KEY_D pourrait être 7
		default: return keycode; // Pour les touches standard
	}
}

int	key_press_handler(int keycode, t_progr *progr)
{
	int	index;

	index = map_key_to_index(keycode);
	if (index >= 0 && index < 256)
		progr->key_states[index] = 1;
	return (0);
}

int	key_release_handler(int keycode, t_progr *progr)
{
	int	index;

	index = map_key_to_index(keycode);
	if (index >= 0 && index < 256)
		progr->key_states[index] = 0;
	return (0);
}