/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 11:56:26 by hwahmane          #+#    #+#             */
/*   Updated: 2025/09/03 13:27:48 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	init_map(t_cub *cub, t_config *cfg)
{
	cub->map.array = cfg->map;
	cub->map.w = cfg->map_w;
	cub->map.h = cfg->map_h;
	cub->map.minimap_width = (cfg->map_w * BLOCK_SIZE) + MINIMAP_SIZE;
	cub->map.minimap_height = (cfg->map_h * BLOCK_SIZE) + MINIMAP_SIZE;
}

static inline void	init_player(t_cub *cub, t_config *cfg)
{
	// Init Player
	cub->p.size = PLY_SIZE;
	cub->p.half = PLY_SIZE / 2;
	get_player_cfg(cub, cfg);
	// MVT
	cub->p.move_up = false;
	cub->p.move_down = false;
	cub->p.move_left = false;
	cub->p.move_right = false;
	cub->p.rotate_left = false;
	cub->p.rotate_right = false;
	cub->p.rotate_up = false;
	cub->p.rotate_down = false;
	cub->p.cosA = cos(cub->p.angle);
	cub->p.sinA = sin(cub->p.angle);
	cub->p.pitch = 0.0;
	cub->p.horizon = cub->half_height;
}

static inline void	init_default_calculation(t_cub *cub)
{
	// Screen
	cub->half_height = HEIGHT / 2;
	cub->half_width = WIDTH / 2;
	// Minimap
	// cub->map.minimap_width = (MAP_WIDTH * BLOCK_SIZE) + MINIMAP_SIZE;
	// cub->map.minimap_height = (MAP_HEIGHT * BLOCK_SIZE) + MINIMAP_SIZE;
	cub->map.padding = MINIMAP_SIZE / 2;
	// Settings
	cub->fps.frame_duration = 1000.0 / TARGET_FPS;
	cub->fov = 60 * (M_PI / 180);
	// Projection Plan
	cub->projection_plane = (cub->half_width) / tan(cub->fov / 2.0);
	// Mouse
	cub->mouse.x = cub->half_width;
	cub->mouse.y = cub->half_height;
}

int	init_cub(t_cub	*cub, t_config *cfg)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (EXIT_FAILURE);
	cub->mlx_win = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "cub3D");
	if (!cub->mlx_win)
		return (EXIT_FAILURE);
	init_default_calculation(cub);
	init_map(cub, cfg);
	init_player(cub, cfg);
	cub->track_mouse = true;
	cub->color[1] = create_trgb(0, cfg->ceil_rgb[0],
					cfg->ceil_rgb[1], cfg->ceil_rgb[2]);
	cub->color[0] = create_trgb(0, cfg->floor_rgb[0],
					cfg->floor_rgb[1], cfg->floor_rgb[2]);
	cub->fps.frames = 0;
	cub->fps.last_time = 0.0;
	cub->fps.last_frame_time = 0.0;
	//! Door
	cub->trigger_door = false;
	cub->door_count = 0;
    ft_bzero(cub->door_entities, sizeof(cub->door_entities));
	return (EXIT_SUCCESS);
}

void	init_image_buffer(t_cub *cub)
{
	cub->img.img_ptr = mlx_new_image(cub->mlx,
			WIDTH, HEIGHT);
	cub->img.img_pixels_ptr = mlx_get_data_addr(cub->img.img_ptr,
			&cub->img.bits_per_pixel, &cub->img.line_length,
			&cub->img.endian);
	cub->img.bytes_per_pixel = cub->img.bits_per_pixel / 8;
	cub->img.pixels = (unsigned int *) cub->img.img_pixels_ptr;
	cub->img.pitch = cub->img.line_length / sizeof(unsigned int);
}

//?: The initial setup of a buffer for the map image require:
//?: The long HORIZONTAL row = MAP_WIDTH
//?: The long VERTICAL = MAP_HIGHT
//?: Padding for each edge = MINIMAP_SIZE / 2
void	init_map_image_buffer(t_cub *cub)
{
	cub->map_img.img_ptr = mlx_new_image(cub->mlx,
			cub->map.minimap_width, cub->map.minimap_height);
	cub->map_img.img_pixels_ptr = mlx_get_data_addr(cub->map_img.img_ptr,
			&cub->map_img.bits_per_pixel, &cub->map_img.line_length,
			&cub->map_img.endian);
	cub->map_img.bytes_per_pixel = cub->map_img.bits_per_pixel / 8;
	cub->map_img.pixels = (unsigned int *) cub->map_img.img_pixels_ptr;
	cub->map_img.pitch = cub->map_img.line_length / sizeof(unsigned int);
	draw_init_minimap(cub);
}
