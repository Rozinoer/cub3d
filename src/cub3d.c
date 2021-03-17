#include "cub3d.h"
#include <stdio.h>

int render_next_frame(t_game *game)
{
    double move_step;
    double newPosX;
    double newPosY;

    move_step = game->player.walk_dir * game->player.move_speed;
    newPosX = (game->player.posX + cos(game->player.rotation_angle + game->player.right_move) * move_step);
    newPosY = (game->player.posY + sin(game->player.rotation_angle + game->player.right_move) * move_step);
    if (game->map.map[(int)(newPosY / TILE_SIZE)][(int)newPosX / TILE_SIZE] != '1')
    {
        game->player.posX = newPosX;
        game->player.posY = newPosY;
    }
    game->player.rotation_angle += game->player.turn_dir * game->player.rotation_speed;
    print_back(game);
    print_map(game);
    print_player(game);
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
    mlx_hook(game->mlx.mlx_win, 3, 1L<<1, key_released, game);
    return (0);
}

int main()
{
    t_game game;
    void *img;
    int *h=NULL;
    int *w=NULL;

    char *path = "../texture/eagle.png";
    img = mlx_xpm_file_to_image(game.mlx.mlx, path, w, h);
    printf("%p", img);
    // sleep(100);
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