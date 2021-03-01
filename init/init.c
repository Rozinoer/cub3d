#include "cub3d.h"

static int init_player(t_game *game)
{
    game->player.posX = 5.0 * TILE_SIZE;
	game->player.posY = 5.0 * TILE_SIZE;
	game->player.radius = 5;
	game->player.turn_dir = 0; // -1 left, +1 right
	game->player.walk_dir = 0;
	game->player.rotation_angle = M_PI * 3 / 2;
	game->player.rotation_speed = 3 * (M_PI / 180);
	game->player.move_speed = 3.0;
	game->player.tick_last_frame = 0;
    return (0);
}

static int init_window(t_game *game)
{
    game->mlx.mlx = mlx_init();
    game->mlx.mlx_win = mlx_new_window(game->mlx.mlx, screenWidth, screenHight, "cub3d");
    return (0);
}

int init(t_game *game)
{
    init_window(game);
    init_player(game);
    return (0);
}