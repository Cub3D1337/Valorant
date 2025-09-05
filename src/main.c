/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 13:48:05 by abnsila           #+#    #+#             */
/*   Updated: 2025/09/05 15:02:19 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>


void print_config(const t_config *cfg)
{
	if (!cfg)
		return;

	printf("Textures:\n");
	printf("  NO: %s\n", cfg->no_texture ? cfg->no_texture : "(null)");
	printf("  SO: %s\n", cfg->so_texture ? cfg->so_texture : "(null)");
	printf("  WE: %s\n", cfg->we_texture ? cfg->we_texture : "(null)");
	printf("  EA: %s\n", cfg->ea_texture ? cfg->ea_texture : "(null)");

	printf("Colors:\n");
	printf("  Floor RGB: %d, %d, %d\n", cfg->floor_rgb[0], cfg->floor_rgb[1], cfg->floor_rgb[2]);
	printf("  Ceiling RGB: %d, %d, %d\n", cfg->ceil_rgb[0], cfg->ceil_rgb[1], cfg->ceil_rgb[2]);

	printf("Map size: %d x %d\n", cfg->map_h, cfg->map_w);
	printf("Map:\n");
	if (cfg->map)
	{
		for (int y = 0; y < cfg->map_h; y++)
			printf("  %s\n", cfg->map[y]);
	}
	else
		printf("  (null)\n");
	printf("Player:\n");
	printf("  Position: (%d, %d)\n", cfg->player_x, cfg->player_y);
	printf("  Direction: %c\n", cfg->player_dir);
}

int	main(int ac, char **av)
{
	t_cub		cub;
	t_config	cfg;

	//TODO: Some map model dont be parsed
	init_config(&cfg);
	if (parsing(ac, av, &cfg) == 0)
		return (EXIT_FAILURE);
	print_config(&cfg);
	init_cub(&cub, &cfg);
	init_textures(&cub, &cfg);
	//! ======================== Door ===========================
	init_doors(&cub);
	//! ======================== Door ===========================
	init_image_buffer(&cub);
	init_map_image_buffer(&cub);
	init_events(&cub);
	mlx_loop(cub.mlx);
	ft_exit(&cub);
	free_config(&cfg);
	return (EXIT_SUCCESS);
}
