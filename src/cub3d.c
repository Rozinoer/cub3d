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
    // game->player.dirX = cos(game->player.rotation_angle);
    // game->player.dirY = sin(game->player.rotation_angle);
    // game->player.planeX = cos(game->player.rotation_angle);
    // game->player.planeY = sin(game->player.rotation_angle);
    print_back(game);
    print_map(game);
    print_player(game);
    print_ray(game);
    mlx_put_image_to_window(game->mlx.mlx, game->mlx.mlx_win, game->data.img, 0, 0);
    return (0);
}

int update(t_game *game)
{
    game->data.img = mlx_new_image(game->mlx.mlx, screenWidth, screenHight);
    game->data.addr = mlx_get_data_addr(game->data.img, &game->data.bits_per_pixel, &game->data.line_length,&game->data.endian);


    mlx_hook(game->mlx.mlx_win, 2, 1L<<0, key_pressed, game);
    render_next_frame(game);
    mlx_hook(game->mlx.mlx_win, 3, 1L<<1, key_released, game);
    return (0);
}

static void get_pos(t_player *player, t_game *game)
{
    int i;
    int j;
    char c;

    i = 0;
    j = 0;
    while (i < game->map.map_size)
    {
        while (game->map.map[i][j] != '\0')
        {
            if (game->map.map[i][j] == 'N' || game->map.map[i][j] == 'S' ||
            game->map.map[i][j] == 'W' || game->map.map[i][j] == 'E')
            {
                c = game->map.map[i][j];
                player->posX = (float)j * TILE_SIZE;
                player->posY = (float)i * TILE_SIZE;
            }
            j++;
        }
        i++;
        j = 0;
    }
    (c == 'N') ? player->rotation_angle = M_PI * 3 / 2 : 0;
    (c == 'S') ? player->rotation_angle = M_PI / 2 : 0 ;
    (c == 'W') ? player->rotation_angle = M_PI : 0;
    (c == 'E') ? player->rotation_angle = 0 : 0;
}

static void init_struct(t_game *game)
{
    t_player player;

    get_pos(&player, game);
    // player.posX = 5.0 * TILE_SIZE;
	// player.posY = 5.0 * TILE_SIZE;
	player.radius = 5;
	player.turn_dir = 0; // -1 left, +1 right
	player.walk_dir = 0;
	// player.rotation_angle = M_PI * 3 / 2;
	player.rotation_speed = 3 * (M_PI / 180);
	player.move_speed = 3.0;
    player.right_move = 0;
    player.left_move = 0;
    game->player = player;

    init(game);
}

int main()
{
    t_game game;

    parser(&game);
    init_struct(&game);
    game.data.img = mlx_new_image(game.mlx.mlx, screenWidth, screenHight);
    game.data.addr = mlx_get_data_addr(game.data.img, &game.data.bits_per_pixel, &game.data.line_length,
                                 &game.data.endian);
                                 
    print_map(&game);
    mlx_loop_hook(game.mlx.mlx, update, &game);
    mlx_loop(game.mlx.mlx);
    return (0);
}