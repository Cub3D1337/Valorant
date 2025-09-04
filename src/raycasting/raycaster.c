/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 16:08:51 by abnsila           #+#    #+#             */
/*   Updated: 2025/09/04 16:19:55 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	init_raycast(t_cub *cub, t_raycast *r, int x, double ray_angle)
{
	r->x = x;
	r->ray_angle = ray_angle;
	r->ray_dir.x = cos(ray_angle);
	r->ray_dir.y = sin(ray_angle);
	r->start_pos.x = cub->p.pos.x;
	r->start_pos.y = cub->p.pos.y;
}

static void recursion(t_cub *cub, t_raycast *r, double accumulated_dist)
{
	t_raycast		new_r;
	t_dda_result	result;
	t_wall_slice	s;
	t_tex_ctx		ctx;

	// Perform DDA
	dda(cub, r, &result);
	// Add the distance of this rayhit_dist to the accumulated distance
	result.dist += accumulated_dist;
	if (result.block_type == DOOR)
	{
		// Move slightly past the door to avoid precision issues
		new_r = *r;
		new_r.start_pos.x = result.hit_point.x + r->ray_dir.x * EPSILON;
		new_r.start_pos.y = result.hit_point.y + r->ray_dir.y * EPSILON;
		// Recurse to find what's behind the door
		recursion(cub, &new_r, result.dist);
	}
	// Convert to perpendicular distance to remove fisheye
	s.perp_dist = result.dist * cos(r->ray_angle - cub->p.angle);
	// Calculate wall height
	s.line_height = (BLOCK_SIZE / s.perp_dist) * cub->projection_plane;
	// Calculate drawing bounds
	s.start_y = cub->half_height - (int)(s.line_height / 2) + (int)cub->p.pitch;
	if (s.start_y < 0) s.start_y = 0;
	s.end_y = cub->half_height + (int)(s.line_height / 2) + (int)cub->p.pitch;
	if (s.end_y >= HEIGHT) s.end_y = HEIGHT - 1;
	// Draw the textured wall column
	ctx = (t_tex_ctx){r->ray_dir, result, r->x, s.line_height, s.start_y, s.end_y};
	mapping_textures(cub, &ctx);
}

static void draw_ray(t_cub *cub, int x, double ray_angle)
{
	t_raycast	r;

	init_raycast(cub, &r, x, ray_angle);
	recursion(cub, &r, 0.0);
}

void	raycasting(t_cub *cub)
{
	double	ray_angle;
	double	angle_step;
	int		x;

	x = 0;
	ray_angle = cub->p.angle - (cub->fov / 2);
	angle_step = cub->fov / WIDTH;
	while (x < WIDTH)
	{
		draw_ray(cub, x, ray_angle);
		ray_angle += angle_step;
		x++;
	}
}
