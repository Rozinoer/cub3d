#include "cub3d.h"

void            my_mlx_pixel_put(t_data data, int x, int y, int color)
{
    char    *dst;

    dst = data.addr + (y * data.line_length + x * (data.bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void get_pos(t_player *player, t_game *game)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < game->map.map_size)
    {
        while (game->map.map[i][j] != '\0')
        {
            if (game->map.map[i][j] == 'N' || game->map.map[i][j] == 'S' ||
            game->map.map[i][j] == 'W' || game->map.map[i][j] == 'E')
            {
                player->direct = game->map.map[i][j];
                player->posX = (float)j * TILE_SIZE;
                player->posY = (float)i * TILE_SIZE;
            }
            j++;
        }
        i++;
        j = 0;
    }
    (player->direct == 'N') ? player->rotation_angle = M_PI * 3 / 2 : 0;
    (player->direct == 'S') ? player->rotation_angle = M_PI / 2 : 0 ;
    (player->direct == 'W') ? player->rotation_angle = M_PI : 0;
    (player->direct == 'E') ? player->rotation_angle = 0 : 0;
}

void init_struct(t_game *game)
{
    t_player player;

    get_pos(&player, game);

	player.radius = 5;
	player.turn_dir = 0; // -1 left, +1 right
	player.walk_dir = 0;
	player.rotation_speed = 3 * (M_PI / 180);
	player.move_speed = 3.0;
    player.right_move = 0;
    player.left_move = 0;

    game->player = player;

    init(game);
}