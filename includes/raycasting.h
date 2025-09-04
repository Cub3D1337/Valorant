/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 14:58:04 by abnsila           #+#    #+#             */
/*   Updated: 2025/09/04 14:43:53 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REYCASTING_H
# define REYCASTING_H

# include "includes.h"

void	raycasting(t_cub *cub);
void	dda(t_cub *cub, t_raycast *r, t_dda_result *result);
void	setup_dda(t_cub *cub, t_dda *dda, t_pointd start_pos, t_pointd ray_dir);

#endif
