/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:55:40 by abnsila           #+#    #+#             */
/*   Updated: 2025/09/02 13:34:50 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <cub3d.h>

static unsigned int	get_texel(const t_img_texture *t, int tx, int ty)
{
	if (!t || !t->img_pixels_ptr || !t->pixels_u32)
		return (0);
	if (tx < 0 || tx >= t->img_width || ty < 0 || ty >= t->img_height)
		return (0);
	return (t->pixels_u32[(unsigned int)ty * t->pitch_u32 + (unsigned int)tx]);
}

// static void	draw_sprite(t_cub *cub, t_img_texture *t)
// {
// 	t_pointi	pos;
// 	int			row;
// 	int			color;
	
// 	pos = (t_pointi){0, 0};
// 	while (pos.y < t->img_height)
// 	{
// 		pos.x = 0;
// 		row = (pos.y + cub->half_height) * cub->img.pitch;
// 		while (pos.x < t->img_width)
// 		{
// 			color = get_texel(t, pos.x, pos.y);
// 			if (color != 0x000000)
// 				cub->img.pixels[row + pos.x + cub->half_width] = color;
// 			pos.x++;
// 		}
// 		pos.y++;
// 	}
// }

static void	draw_sprite(t_cub *cub, t_img_texture *t, int scale)
{
	t_pointi	pos;
	int			row;
	int			color;
	int			scaled_w;
	int			scaled_h;
	int			tx;
	int			ty;

	scaled_w = t->img_width * scale;
	scaled_h = t->img_height * scale;
	pos = (t_pointi){0, 0};
	while (pos.y < scaled_h)
	{
		pos.x = 0;
		row = (pos.y + cub->half_height - (scaled_h / 2)) * cub->img.pitch;
		while (pos.x < scaled_w)
		{
			// map destination pixel back to source
			tx = pos.x / scale;
			ty = pos.y / scale;
			color = get_texel(t, tx, ty);
			if (color != 0x000000)
				cub->img.pixels[row + pos.x + cub->half_width - (scaled_w / 2)] = color;
			pos.x++;
		}
		pos.y++;
	}
}

void animation(t_cub *cub)
{
    static int frame = 0;        // current sprite frame [0..7]
    static int counter = 0;      // delay counter

    int delay = 10; // higher = slower animation (adjust per FPS)

    // Draw current frame
    draw_sprite(cub, &cub->sprites[frame], 1);

    // Advance every `delay` frames
    if (++counter >= delay)
    {
        counter = 0;
        frame = (frame + 1) % 8; // loop back to 0
    }
}
