/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 10:28:06 by hwahmane          #+#    #+#             */
/*   Updated: 2025/09/04 18:16:57 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

# include "./typedef/global.h"
# include "./typedef/dda.h"
# include "./typedef/tex_type.h"
# include "settings.h"

typedef struct s_map_data
{
	// int	array[MAP_HEIGHT][MAP_WIDTH];
	char	**array;
	int	w;
	int	h;
	int	minimap_width;
	int	minimap_height;
	int	padding;
}				t_map_data;

typedef struct t_map_ctx
{
	t_pointd		s;
	t_pointd		e;
	t_pointd		norm_ply_pos;
	t_pointi		rows;
}			t_map_ctx;

typedef struct s_img
{
	// Fast rendering
	unsigned int	*pixels;
	unsigned int	pitch;
	// Img members
	void	*img_ptr;
	char	*img_pixels_ptr;
	int		bits_per_pixel;
	int		bytes_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_player
{
	t_pointd	pos;
	t_pointd	prev_pos;
	int		size;
	int		half;
	t_bool	move_up;
	t_bool	move_down;
	t_bool	move_left;
	t_bool	move_right;
	t_bool	rotate_left;
	t_bool	rotate_right;
	double	angle;
	double	cosA;
	double	sinA;
	double	pitch;
	double	horizon;
	t_bool	rotate_up;
	t_bool	rotate_down;
}				t_player;

typedef struct	s_fps
{
	int			frames;
	int			fps;
	double		last_time;
	double		last_frame_time;
	double		delta_time;
	double		frame_duration;
}				t_fps;


//! ======================== Door ===========================
typedef enum e_door_state
{
    DOOR_CLOSED,
    DOOR_OPENING,
    DOOR_OPEN,
    DOOR_CLOSING
}   t_door_state;

#define MAX_DOORS 64
#define DOOR_FRAMES 17          // frames indexed 0..8
#define DOOR_TIMER_DELAY 10     // adjust animation speed


typedef struct s_door_anim
{
	int             map_x;
    int             map_y;
    int             frame;       // current frame [0..8]
    t_door_state    state;
    int             timer;       // delay counter
}   t_door_anim;
//! ======================== Door ===========================


typedef struct s_cub
{
	void		*mlx;
	void		*mlx_win;
	int			half_height;
	int			half_width;
	t_img		img;
	t_img		map_img;
	t_map_data	map;
	t_player	p;
	// Textures
	t_img_texture	textures[5];
	t_img_texture	sprites[8];
	t_img_texture	doors[MAX_DOORS];
	//TODO: Default calculation
	double	fov;
	// Projection Plan
	double		projection_plane;
	// COLOR
	int			color[2];
	// Mouse
	t_pointd	mouse;
	t_bool		track_mouse;
	t_fps		fps;
	//! ======================== Door ===========================
	t_bool		trigger_door;
	t_door_anim     door_entities[MAX_DOORS];
    int             door_count;
	//! ======================== Door ===========================
}			t_cub;

#endif
