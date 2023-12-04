/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:04:31 by cmansey           #+#    #+#             */
/*   Updated: 2023/12/03 13:33:26 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	key_press_handler(int key, t_progr *progr)
{
	progr->key_states[key] = 1;
	return (0);
}

int	key_release_handler(int key, t_progr *progr)
{
	progr->key_states[key] = 0;
	return (0);
}
