/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:35:11 by abnsila           #+#    #+#             */
/*   Updated: 2025/09/03 16:41:26 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	draw_map_square(t_cub *cub, t_pointi pos, int size, int color)
{
	t_pointi	incr_pos;

	incr_pos.y = 0;
	while (incr_pos.y < size)
	{
		incr_pos.x = 0;
		while (incr_pos.x < size)
		{
			cub->map_img.pixels[(pos.y + incr_pos.y) * cub->map_img.pitch
				+ (pos.x + incr_pos.x)] = color;
			incr_pos.x++;
		}
		incr_pos.y++;
	}
}

static void	draw_rect(t_cub *cub, t_rect rect)
{
	t_pointi	start;
	t_pointi	end;
	int			x;
	int			row;

	if (rect.side == HORIZONTAL)
	{
		start = (t_pointi){rect.pos.x, rect.pos.y};
		end = (t_pointi){rect.pos.x + rect.len, rect.pos.y + rect.wid};
	}
	else
	{
		start = (t_pointi){rect.pos.x, rect.pos.y};
		end = (t_pointi){rect.pos.x + rect.wid, rect.pos.y + rect.len};
	}
	while (start.y < end.y)
	{
		x = start.x;
		row = start.y * cub->img.pitch;
		while (x < end.x)
			cub->img.pixels[row + x++] = rect.color;
		start.y++;
	}
}

static void	draw_border(t_cub *cub)
{
	t_rect	data;

	data = (t_rect){(t_pointi){0, 0}, MINIMAP_SIZE + (BORDER * 2),
		BORDER, HORIZONTAL, 0xcccccc};
	draw_rect(cub, data);
	data = (t_rect){(t_pointi){0, MINIMAP_SIZE + BORDER},
		MINIMAP_SIZE + (BORDER * 2), BORDER, HORIZONTAL, 0xcccccc};
	draw_rect(cub, data);
	data = (t_rect){(t_pointi){0, BORDER}, MINIMAP_SIZE + BORDER,
		BORDER, VERTICAL, 0xcccccc};
	draw_rect(cub, data);
	data = (t_rect){(t_pointi){MINIMAP_SIZE + BORDER, BORDER},
		MINIMAP_SIZE + BORDER, BORDER, VERTICAL, 0xcccccc};
	draw_rect(cub, data);
}

void	draw_init_minimap(t_cub *cub)
{
	t_pointi	pos;
	int			color;

	ft_memset(cub->map_img.img_pixels_ptr, 0,
		cub->map.minimap_height * cub->map_img.line_length);
	pos.y = 0;
	while (pos.y < cub->map.h)
	{
		pos.x = 0;
		while (pos.x < cub->map.w)
		{
			if (cub->map.array[pos.y][pos.x] == '1')
				color = 0xffffff;
			//! ====================== Door =========================
			else if (cub->map.array[pos.y][pos.x] == 'D')
            {
				color = 0x5555ff;
				cub->door_entities[cub->door_count].map_x = pos.x;
                cub->door_entities[cub->door_count].map_y = pos.y;
                cub->door_entities[cub->door_count].frame = 0;
                cub->door_entities[cub->door_count].state = DOOR_CLOSED;
                cub->door_entities[cub->door_count].timer = 0;
                cub->door_count++;
            }
			//! ====================== Door =========================
			// else if (cub->map.array[pos.y][pos.x] == 'd')
			// 	color = 0x9999ff;
			else
				color = 0x333333;
			draw_map_square(cub,
				(t_pointi){cub->map.padding + pos.x * BLOCK_SIZE,
				cub->map.padding + pos.y * BLOCK_SIZE},
				BLOCK_SIZE, color);
			pos.x++;
		}
		pos.y++;
	}
}

void	draw_minimap(t_cub *cub)
{
	t_map_ctx		ctx;
	t_pointi		pos;
	t_pointi		cord;
	int				color;

	draw_border(cub);
	ctx.norm_ply_pos.x = cub->p.pos.x + cub->map.padding;
	ctx.norm_ply_pos.y = cub->p.pos.y + cub->map.padding;
	ctx.s.x = ctx.norm_ply_pos.x - cub->map.padding;
	ctx.e.x = ctx.norm_ply_pos.x + cub->map.padding;
	ctx.s.y = ctx.norm_ply_pos.y - cub->map.padding;
	ctx.e.y = ctx.norm_ply_pos.y + cub->map.padding;
	ctx.rows.x = (int)(ctx.e.x - ctx.s.x + 0.5);
	ctx.rows.y = (int)(ctx.e.y - ctx.s.y + 0.5);
	pos.y = -1;
	while (++pos.y < ctx.rows.y)
	{
		pos.x = 0;
		while (pos.x < ctx.rows.x)
		{
			cord = (t_pointi){(int)ctx.s.x + pos.x, (int)ctx.s.y + pos.y};
			color = cub->map_img.pixels[cord.y * cub->map_img.pitch + cord.x];
			put_pixel(cub, pos.x++ + BORDER, pos.y + BORDER, color);
		}
	}
}
