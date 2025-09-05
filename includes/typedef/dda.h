/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:27:26 by abnsila           #+#    #+#             */
/*   Updated: 2025/09/05 15:32:55 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DDA_H
# define DDA_H

# include "global.h"

typedef enum s_block_type
{
	NONE,
	OUT,
	WALL,
	DOOR,
}			t_block_type;

typedef struct s_dda
{
	t_pointi	map_pos;
	t_pointd	p_cell;
	t_pointi	dir_step;
	t_pointd	grid_step;
	t_bool		hit;
	t_side		side;			
	t_pointd	hypotenuse_dist;
}				t_dda;

typedef struct s_dda_result
{
	t_side			side;
	t_pointi		dir_step;
	t_pointi		map_pos;
	t_pointd		hit_point;
	double			dist;
	t_block_type	block_type;
}				t_dda_result;

typedef struct s_wall_slice
{
	double	perp_dist;
	double	line_height;
	int		start_y;
	int		end_y;
}			t_wall_slice;

typedef struct s_raycast
{
	int				x;
	double			ray_angle;
	t_pointd		ray_dir;
	t_pointd		start_pos;
}				t_raycast;

#endif
