#include "cub3d.h"
#include <stdio.h>

int render_next_frame(t_game *game)
{
    print_back(game);
    print_ray(game);

    mlx_put_image_to_window(game->mlx.mlx, game->mlx.mlx_win, game->data.img, 0, 0);
    return (0);
}

int update(t_game *game)
{
    game->data.img = mlx_new_image(game->mlx.mlx, game->mlx.win_width, game->mlx.win_hight);
    game->data.addr = mlx_get_data_addr(game->data.img, &game->data.bits_per_pixel, &game->data.line_length,&game->data.endian);


    mlx_hook(game->mlx.mlx_win, 2, 1L<<0, key_pressed, game);
    render_next_frame(game);
    return (0);
}

int main()
{
    t_game game;

    parser(&game);
    init_struct(&game);
    game.data.img = mlx_new_image(game.mlx.mlx, game.mlx.win_width, game.mlx.win_hight);
    game.data.addr = mlx_get_data_addr(game.data.img, &game.data.bits_per_pixel, &game.data.line_length,
                                 &game.data.endian);                         
    print_map(&game);
    mlx_loop_hook(game.mlx.mlx, update, &game);
    mlx_loop(game.mlx.mlx);
    return (0);
}