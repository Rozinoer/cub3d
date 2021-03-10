#include "cub3d.h"


static int init_window(t_game *game)
{
    game->mlx.mlx = mlx_init();
    game->mlx.mlx_win = mlx_new_window(game->mlx.mlx, screenWidth, screenHight, "cub3d");
    return (0);
}

int init(t_game *game)
{
    init_window(game);
    return (0);
}