/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 11:54:31 by hwahmane          #+#    #+#             */
/*   Updated: 2025/09/04 19:00:18 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void update_doors(t_cub *cub)
{
    for (int i = 0; i < cub->door_count; ++i)
    {
        t_door_anim *door = &cub->door_entities[i];

        // Only update if door is in motion
        if (door->state == DOOR_CLOSED || door->state == DOOR_OPEN)
            continue;

        // increment timer; only update frame when it reaches the delay
        if (++door->timer < DOOR_TIMER_DELAY)
            continue;
        door->timer = 0;

        if (door->state == DOOR_OPENING)
        {
            if (door->frame < DOOR_FRAMES - 1)
            {
                door->frame++;
                printf("Door opening: frame %d\n", door->frame); // Debug
            }
            else
            {
                // reached final open frame
                door->state = DOOR_OPEN;
                // mark cell as non-blocking
                cub->map.array[door->map_y][door->map_x] = 'd';
                printf("Door fully open\n"); // Debug
            }
        }
        else if (door->state == DOOR_CLOSING)
        {
            if (door->frame > 0)
            {
                door->frame--;
                printf("Door closing: frame %d\n", door->frame); // Debug
            }
            else
            {
                // fully closed
                door->state = DOOR_CLOSED;
                // mark cell as blocking again
                cub->map.array[door->map_y][door->map_x] = 'D';
                printf("Door fully closed\n"); // Debug
            }
        }
    }
}


int	ft_loop_hook(t_cub *cub)
{
	double	current;
	double	frame_time;

	current = get_time_ms();
	frame_time = current - cub->fps.last_frame_time;
	if (frame_time < cub->fps.frame_duration)
		return (EXIT_SUCCESS);
	cub->fps.delta_time = frame_time / 1000.0;
	cub->fps.last_frame_time = current;
	cub->fps.frames++;
	if (current - cub->fps.last_time >= 1000.0)
	{
		cub->fps.fps = cub->fps.frames;
		cub->fps.frames = 0;
		cub->fps.last_time = current;
	}
	mouse_handler(cub);
	move(cub);
	update_doors(cub);
	render(cub);
	return (EXIT_SUCCESS);
}

// TODO: On mouse IN / On Mouse OUT
void	init_events(t_cub *cub)
{
	mlx_hook(cub->mlx_win, ON_KEYDOWN, KeyPressMask, ft_key_press, cub);
	mlx_hook(cub->mlx_win, ON_KEYUP, KeyReleaseMask, ft_key_release, cub);
	mlx_hook(cub->mlx_win, ON_DESTROY, DestroyNotifyMask, ft_exit, cub);
	mlx_mouse_hide(cub->mlx, cub->mlx_win);
	mlx_hook(cub->mlx_win, ON_MOUSEMOVE, PointerMotionMask, ft_mouse_move, cub);
	mlx_loop_hook(cub->mlx, ft_loop_hook, cub);
}
