/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 12:41:46 by hwahmane          #+#    #+#             */
/*   Updated: 2025/09/03 15:55:58 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	rotate(t_cub *cub)
{
	t_pointd	rot_speed;

	if (cub->p.rotate_left || cub->p.rotate_right)
	{
		rot_speed.x = H_ROT_SPEED * cub->fps.delta_time;
		if (cub->p.rotate_left)
		{
			cub->p.angle -= rot_speed.x;
		}
		else if (cub->p.rotate_right)
		{
			cub->p.angle += rot_speed.x;
		}
		if (cub->p.angle < 0)
			cub->p.angle += 2 * M_PI;
		if (cub->p.angle >= 2 * M_PI)
			cub->p.angle -= 2 * M_PI;
		cub->p.cosA = cos(cub->p.angle);
		cub->p.sinA = sin(cub->p.angle);
	}

	if (cub->p.rotate_up || cub->p.rotate_down)
	{
		// Update pitch (up/down)
		rot_speed.y = V_ROT_SPEED * cub->fps.delta_time;
		if (cub->p.rotate_up)
			cub->p.pitch += rot_speed.y;
		else if (cub->p.rotate_down)
			cub->p.pitch -= rot_speed.y;
		if (cub->p.pitch > MAX_PITCH) 
			cub->p.pitch = MAX_PITCH;
		if (cub->p.pitch < MIN_PITCH) 
			cub->p.pitch = MIN_PITCH;
		cub->p.horizon = (cub->half_height) + (int)cub->p.pitch;
	}
}

static t_bool	check_boundaries(t_cub *cub)
{
	t_pointi	ply_corners[4];
	t_pointi	map;
	t_pointd	p;
	int			h;
	int			i;

	p.x = cub->p.pos.x;
	p.y = cub->p.pos.y;
	h = cub->p.half;
	// --- Check last boundarie wall to avoid undefined behaviore on raycasting and texture mapping ---
	if ((int)p.x - h < BLOCK_SIZE
		|| (int) p.x + h >= (cub->map.w * BLOCK_SIZE) + 1 - BLOCK_SIZE
		|| (int)p.y - h < BLOCK_SIZE
		|| (int)p.y + h >= (cub->map.h * BLOCK_SIZE) + 1 - BLOCK_SIZE)
			return (false);
	// --- Define player hitbox corners ---
	ply_corners[0] = (t_pointi) {(int)(p.x - h), (int)(p.y - h)}; // top-left
	ply_corners[1] = (t_pointi) {(int)(p.x + h - 1), (int)(p.y - h)}; // top-right
	ply_corners[2] = (t_pointi) {(int)(p.x - h), (int)(p.y + h - 1)}; // bottom-left
	ply_corners[3] = (t_pointi) {(int)(p.x + h - 1), (int)(p.y + h - 1)}; // bottom-right
	i = 0;
	while (i < 4)
	{
		map.x = ply_corners[i].x / BLOCK_SIZE;
		map.y = ply_corners[i].y / BLOCK_SIZE;
		if (cub->map.array[map.y][map.x] == '1'
		|| cub->map.array[map.y][map.x] == 'D')
			return (false);
		i++;
	}
	return (true);
}

static void	move_with_steps(t_cub *cub, t_pointd delta)
{
	double		len;
	int			steps;
	t_pointd	delta_steps;

	len = sqrt(delta.x * delta.x + delta.y * delta.y);
	steps = (int)(len / TINY_STEP);
	if (steps <= 0)
		steps = 1;
	delta_steps.x = delta.x / steps;
	delta_steps.y = delta.y / steps;
	while (steps--)
	{
		cub->p.pos.x += delta_steps.x;
		if (!check_boundaries(cub))
			cub->p.pos.x -= delta_steps.x;
		cub->p.pos.y += delta_steps.y;
		if (!check_boundaries(cub))
			cub->p.pos.y -= delta_steps.y;
	}
}

// UP / DOWN
//? The cos and sin give the percent of tilt for the x and y axis
//? so this percent for eaxh side is mulipated by speed
//? (conclusion: we get the speed for each axe)
//? we get the full angle because this is the player view angle
// LEFT / RIGHT
//? We get the (full angle -+ quadrant)
//? because this is the player left and right edges
//? same mvt applyed for those edges
static void	update_position(t_cub *cub, t_pointd delta, double speed)
{
	if (cub->p.move_up)
	{
		delta.x += cub->p.cosA * speed;
		delta.y += cub->p.sinA * speed;
	}
	if (cub->p.move_down)
	{
		delta.x -= cub->p.cosA * speed;
		delta.y -= cub->p.sinA * speed;
	}
	if (cub->p.move_left)
	{
		delta.x += cos(cub->p.angle - M_PI_2) * speed;
		delta.y += sin(cub->p.angle - M_PI_2) * speed;
	}
	if (cub->p.move_right)
	{
		delta.x += cos(cub->p.angle + M_PI_2) * speed;
		delta.y += sin(cub->p.angle + M_PI_2) * speed;
	}
	if (delta.x != 0 || delta.y != 0)
		move_with_steps(cub, delta);
}

void	move(t_cub *cub)
{
	t_pointd	delta;
	double		speed;

	if (cub->p.rotate_left || cub->p.rotate_right
		|| cub->p.rotate_up || cub->p.rotate_down)
		rotate(cub);
	if (cub->p.move_up || cub->p.move_down
		|| cub->p.move_left || cub->p.move_right)
	{
		delta = (t_pointd){0, 0};
		speed = SPEED * cub->fps.delta_time;
		update_position(cub, delta, speed);
	}
}
