#include "cub3d.h"


static int init_window(t_game *game)
{
    game->mlx.mlx = mlx_init();
    game->mlx.mlx_win = mlx_new_window(game->mlx.mlx, game->mlx.win_width, game->mlx.win_hight, "cub3d");
    return (0);
}

int init(t_game *game)
{
    init_window(game);
    return (0);
}