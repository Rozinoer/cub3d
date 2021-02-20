#include "cub3d.h"
#include <stdio.h>

void            my_mlx_pixel_put(t_data data, int x, int y, int color)
{
    char    *dst;

    dst = data.addr + (y * data.line_length + x * (data.bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int render_next_frame(t_game *game)
{
    print_map(game);
	print_player(game);
    print_ray(game);
    mlx_put_image_to_window(game->mlx.mlx, game->mlx.mlx_win, game->data.img, 0, 0);
    printf("render\n");
    
    return (0);
}

int update(t_game *game)
{
    double move_step;

    mlx_hook(game->mlx.mlx_win, 2, 1L<<0, key_pressed, game);
    
    move_step = game->player.walk_dir * game->player.move_speed;
    game->player.posX = (int)(game->player.posX + cos(game->player.rotation_angle) * move_step) ;
    game->player.posY= (int)(game->player.posY + sin(game->player.rotation_angle) * move_step) ;
    game->player.rotation_angle += game->player.turn_dir * game->player.rotation_speed;
    render_next_frame(game);

    mlx_hook(game->mlx.mlx_win, 3, 1L<<1, key_released, game);
    return (0);
}

int main()
{
    t_game game;
    game.data.img = mlx_new_image(game.mlx.mlx, 1920, 1080);
    game.data.addr = mlx_get_data_addr(game.data.img, &game.data.bits_per_pixel, &game.data.line_length,
                                 &game.data.endian);
    parser(&game);
    init(&game);
    print_map(&game);
    mlx_loop_hook(game.mlx.mlx, update, &game);
    mlx_loop(game.mlx.mlx);
    return (0);
}