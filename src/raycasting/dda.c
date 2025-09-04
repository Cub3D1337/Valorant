/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 18:18:32 by abnsila           #+#    #+#             */
/*   Updated: 2025/09/04 16:21:34 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static t_block_type	get_block_type(t_cub *cub, int x, int y)
{
	// Check Map Bounds
	if (x < 0 || x >= cub->map.w
	|| y < 0 || y >= cub->map.h)
		return (NONE);
	// Wall && Close Door Hit
	else if (cub->map.array[y][x] == '1')
		return (WALL);
	else if (cub->map.array[y][x] == 'D')
		return (DOOR);
	else
		return (NONE);
}

static void	setup_dir_step(t_dda *dda, t_pointd ray_dir)
{
	if (ray_dir.x < 0)
		dda->dir_step.x = -1;
	else
		dda->dir_step.x = 1;
	if (ray_dir.y < 0)
		dda->dir_step.y = -1;
	else
		dda->dir_step.y = 1;
}

void	setup_dda(t_cub *cub, t_dda *dda, t_pointd start_pos, t_pointd ray_dir)
{
	// Get player pos in grid map, the value truncate to int
	// Those values is modified after each jump to check collision with wall 
	dda->p_cell.x = start_pos.x / BLOCK_SIZE;
	dda->p_cell.y = start_pos.y / BLOCK_SIZE;
	// Like p_pos but whitout the fractional part
	dda->map_pos.x = (int)dda->p_cell.x;
	dda->map_pos.y = (int)dda->p_cell.y;

	// Grid jump step on x and y (Horizontal and Vertical)
	dda->grid_step.x = fabs(1 / ray_dir.x);
	dda->grid_step.y = fabs(1 / ray_dir.y);
	// Setup initial hypotenuse_dist (x, y) lenght to begin a simple and constant jump grid
	if (ray_dir.x < 0)
		dda->hypotenuse_dist.x = (dda->p_cell.x - dda->map_pos.x) * dda->grid_step.x;
	else
		dda->hypotenuse_dist.x = ((dda->map_pos.x + 1) - dda->p_cell.x) * dda->grid_step.x;
	if (ray_dir.y < 0)
		dda->hypotenuse_dist.y = (dda->p_cell.y - dda->map_pos.y) * dda->grid_step.y;
	else
		dda->hypotenuse_dist.y = ((dda->map_pos.y + 1) - dda->p_cell.y) * dda->grid_step.y;
	// Setup dir step
	setup_dir_step(dda, ray_dir);
}

static void	compute_ray_lenght(t_cub *cub, t_dda *dda, t_raycast *r, t_dda_result *result)
{
	//? Store info for Textures process
	result->side = dda->side;
	result->dir_step = dda->dir_step;
	result->map_pos.x = dda->map_pos.x;
	result->map_pos.y = dda->map_pos.y;
	//? Use the last side distance depending on hit side
	if (dda->side == HORIZONTAL)
	{
		result->dist = (dda->map_pos.x - (dda->p_cell.x)
			+ (1 - dda->dir_step.x) / 2) / r->ray_dir.x;
	}
	else
	{		
		result->dist = (dda->map_pos.y - (dda->p_cell.y)
			+ (1 - dda->dir_step.y) / 2) / r->ray_dir.y;
	}
	result->dist *= BLOCK_SIZE;
	//? Final position = Start position + Direction × Distance
	result->hit_point.x = r->start_pos.x + (r->ray_dir.x * result->dist);
	result->hit_point.y = r->start_pos.y + (r->ray_dir.y * result->dist);
}

void	dda(t_cub *cub, t_raycast *r, t_dda_result *result)
{
	t_dda			dda;
	t_block_type	block_type;

	block_type = NONE;
	setup_dda(cub, &dda, r->start_pos, r->ray_dir);
	while (block_type == NONE)
	{
		if (dda.hypotenuse_dist.x <= dda.hypotenuse_dist.y)
		{
			dda.hypotenuse_dist.x += dda.grid_step.x;
			dda.map_pos.x += dda.dir_step.x;
			dda.side = HORIZONTAL;
		}
		else
		{
			dda.hypotenuse_dist.y += dda.grid_step.y;
			dda.map_pos.y += dda.dir_step.y;	
			dda.side = VERTICAL;
		}
		block_type = get_block_type(cub, dda.map_pos.x, dda.map_pos.y);
		if (block_type != NONE)
			result->block_type = get_block_type(cub, dda.map_pos.x, dda.map_pos.y);
	}
	compute_ray_lenght(cub, &dda, r, result);
}
