/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 21:17:29 by abnsila           #+#    #+#             */
/*   Updated: 2025/09/02 17:08:49 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	set_texture_paths(t_cub *cub, t_config *cfg)
{
	cub->textures[NORTH].relative_path = cfg->no_texture;
	cub->textures[SOUTH].relative_path = cfg->so_texture;
	cub->textures[WEST].relative_path = cfg->we_texture;
	cub->textures[EAST].relative_path = cfg->ea_texture;
	cub->textures[DOOR].relative_path = "./textures/animation/door/door_0.xpm";
}

static void	prepare_texture_metadata(t_cub *cub, int i)
{
	t_img_texture	*t;

	t = &cub->textures[i];
	t->img_pixels_ptr = mlx_get_data_addr(
				t->img_ptr, &t->bits_per_pixel,
				&t->line_length, &t->endian
				);
	t->pixels_u32 = (unsigned int *)t->img_pixels_ptr;
	t->pitch_u32 = (unsigned int)(t->line_length / sizeof(unsigned int));
}

//TODO: diffrent from door
int	init_textures(t_cub *cub, t_config *cfg)
{
	int	i;

	i = 0;
	set_texture_paths(cub, cfg);
	while (i < TEX_NUM)
	{
		cub->textures[i].img_ptr = mlx_xpm_file_to_image(
				cub->mlx,
				cub->textures[i].relative_path,
				&cub->textures[i].img_width,
				&cub->textures[i].img_height
				);
		if (!cub->textures[i].img_ptr)
		{
			printf("Failed to load tex: %s\n", cub->textures[i].relative_path);
			return (EXIT_FAILURE);
		}
		prepare_texture_metadata(cub, i);
		i++;
	}
	return (EXIT_SUCCESS);
}




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
