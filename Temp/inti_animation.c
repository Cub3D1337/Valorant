/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inti_animation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:03:19 by abnsila           #+#    #+#             */
/*   Updated: 2025/09/05 15:03:36 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

// ================================= Animated sprites ===============================

static void	set_sprites_paths(t_cub *cub)
{
	// 8 frames
	cub->sprites[0].relative_path = "./textures/animation/spin/blue_sprits_0.xpm";
	cub->sprites[1].relative_path = "./textures/animation/spin/blue_sprits_1.xpm";
	cub->sprites[2].relative_path = "./textures/animation/spin/blue_sprits_2.xpm";
	cub->sprites[3].relative_path = "./textures/animation/spin/blue_sprits_3.xpm";
	cub->sprites[4].relative_path = "./textures/animation/spin/blue_sprits_4.xpm";
	cub->sprites[5].relative_path = "./textures/animation/spin/blue_sprits_5.xpm";
	cub->sprites[6].relative_path = "./textures/animation/spin/blue_sprits_6.xpm";
	cub->sprites[7].relative_path = "./textures/animation/spin/blue_sprits_7.xpm";
}

static void	prepare_sprite_metadata(t_cub *cub, int i)
{
	t_img_texture	*t;

	t = &cub->sprites[i];
	t->img_pixels_ptr = mlx_get_data_addr(
				t->img_ptr, &t->bits_per_pixel,
				&t->line_length, &t->endian
				);
	t->pixels_u32 = (unsigned int *)t->img_pixels_ptr;
	t->pitch_u32 = (unsigned int)(t->line_length / sizeof(unsigned int));
}

int	init_sprites(t_cub *cub)
{
	int	i;
	
	i = 0;
	set_sprites_paths(cub);
	// Init sprites image buffers
	while (i < 8)
	{
		cub->sprites[i].img_ptr = mlx_xpm_file_to_image(
				cub->mlx,
				cub->sprites[i].relative_path,
				&cub->sprites[i].img_width,
				&cub->sprites[i].img_height
				);
		if (!cub->sprites[i].img_ptr)
		{
			printf("Failed to load sprite: %s\n", cub->sprites[i].relative_path);
			return (EXIT_FAILURE);
		}
		prepare_sprite_metadata(cub, i);
		i++;
	}
	return (EXIT_SUCCESS);
}
