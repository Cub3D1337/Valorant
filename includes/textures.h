/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 10:50:00 by abnsila           #+#    #+#             */
/*   Updated: 2025/09/02 20:51:43 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURES_H
# define TEXTURES_H

# include "includes.h"

int		init_textures(t_cub *cub, t_config *cfg);
void	mapping_textures(t_cub *cub, t_tex_ctx *ctx);
// Doors sprites
int	init_doors(t_cub *cub);
// Animated sprites
int		init_sprites(t_cub *cub);
void	animation(t_cub *cub);

#endif
