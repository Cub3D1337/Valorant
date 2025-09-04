/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 10:48:21 by abnsila           #+#    #+#             */
/*   Updated: 2025/09/04 18:57:45 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static unsigned int	get_texel(const t_img_texture *t, int tx, int ty)
{
	if (!t || !t->img_pixels_ptr || !t->pixels_u32)
		return (0);
	if (tx < 0 || tx >= t->img_width || ty < 0 || ty >= t->img_height)
		return (0);
	return (t->pixels_u32[(unsigned int)ty * t->pitch_u32 + (unsigned int)tx]);
}

static void	get_tex(t_cub *cub,
	t_tex_ctx *ctx, t_texture_data *data)
{
	(void)ctx;
	t_pointi	cord;

	cord.y = (ctx->result.map_pos.y);
	cord.x = (ctx->result.map_pos.x);

	// if (cub->map.array[cord.y][cord.x] == 'D')
	// 	data->tex = &cub->textures[DOOR];
	
	//! ======================== Door ===========================
	// Always check if there’s a door entity at this cell
	for (int i = 0; i < cub->door_count; i++)
	{
		if (cub->door_entities[i].map_x == cord.x &&
			cub->door_entities[i].map_y == cord.y)
		{
			int frame = cub->door_entities[i].frame;
			// printf("Door Frame: %d\n", frame);
			data->tex = &cub->doors[frame];
			return ; // stop here, door has priority
		}
	}
	//! ======================== Door ===========================


	// Commented just for testing door only
	if (ctx->result.side == VERTICAL && ctx->result.dir_step.y == 1)
		data->tex = &cub->textures[NORTH_TEX];
	else if (ctx->result.side == VERTICAL && ctx->result.dir_step.y == -1)
		data->tex = &cub->textures[SOUTH_TEX];
	else if (ctx->result.side == HORIZONTAL && ctx->result.dir_step.x == 1)
		data->tex = &cub->textures[EAST_TEX];
	else if (ctx->result.side == HORIZONTAL && ctx->result.dir_step.x == -1)
		data->tex = &cub->textures[WEST_TEX];
}

static void	setup(t_cub *cub, t_tex_ctx *ctx, t_texture_data *data)
{
	// 1) Use exact hit position from DDA (avoids compression artifacts)
	if (ctx->result.side == HORIZONTAL)
		data->wallX = ctx->result.hit_point.y / BLOCK_SIZE;
	else
		data->wallX = ctx->result.hit_point.x / BLOCK_SIZE;
	// Get correct texture img
	get_tex(cub, ctx, data);

	// fractional part only from hited col
	data->wallX -= floor(data->wallX);
	// 2) Texture column index
	data->tex_cord.x = (int)(data->wallX * data->tex->img_width);
	if ((ctx->result.side == HORIZONTAL && ctx->ray_dir.x > 0) ||
		(ctx->result.side == VERTICAL && ctx->ray_dir.y < 0))
	{
		data->tex_cord.x = data->tex->img_width - data->tex_cord.x - 1;
	}

	// 3) Step: how much to move in texture for each screen pixel
	data->step = (double)data->tex->img_height / ctx->line_height;
	// 4) Initial texture y position
	// We start drawing partway into the texture, because the top part of the wall is off-screen.
	data->tex_pos = (ctx->start_y - cub->p.horizon + ctx->line_height / 2.0) * data->step;
}

void	mapping_textures(t_cub *cub, t_tex_ctx *ctx)
{
	t_texture_data	data;
	
	setup(cub, ctx, &data);
	// 5) Draw vertical stripe
	while (ctx->start_y <= ctx->end_y)
	{
		data.tex_cord.y = (int)data.tex_pos;
		if (data.tex_cord.y < 0)
			data.tex_cord.y = 0;
		if (data.tex_cord.y >= data.tex->img_height)
			data.tex_cord.y = data.tex->img_height - 1;

		data.color = get_texel(data.tex, data.tex_cord.x, data.tex_cord.y);
		if (check_minimap_edge(ctx->x, ctx->start_y))
			if (data.color != 0xFF000000)
				cub->img.pixels[ctx->start_y * cub->img.pitch + ctx->x] = data.color;
		data.tex_pos += data.step;
		ctx->start_y++;
	}
}
