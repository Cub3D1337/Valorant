/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:24:14 by abnsila           #+#    #+#             */
/*   Updated: 2025/09/04 14:59:57 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H

# include "../Libft/includes/libft.h"

typedef enum e_side
{
	HORIZONTAL,
	VERTICAL,
}			t_side;

typedef enum e_tex_side
{
	SOUTH_TEX,
	NORTH_TEX,
	WEST_TEX,
	EAST_TEX,
	DOOR_TEX,
}			t_tex_side;

typedef enum e_door_status
{
	CLOSE,
	OPEN,
}			t_door_status;

typedef struct s_pointi
{
	int	x;
	int	y;
}				t_pointi;

typedef struct s_pointd
{
	double	x;
	double	y;
}				t_pointd;

typedef struct s_rect
{
	t_pointi	pos;
	int			len;
	int			wid;
	t_side		side;
	int			color;
}				t_rect;

typedef struct s_line
{
	t_pointi	start;
	double		angle;
	int			line_len;
	int			color;
}				t_line;

#endif
