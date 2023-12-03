/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:39:02 by cmansey           #+#    #+#             */
/*   Updated: 2023/12/03 13:31:19 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_no_player(void)
{
	printf("Error\nPlayer is not valid or not found.\n");
	printf("Check also if the map exist.\n");
	exit (EXIT_FAILURE);
	return (0);
}
