#include "cub3d.h"
#define FOV 0.66
void            my_mlx_pixel_put(t_data data, int x, int y, int color)
{
    char    *dst;

    dst = data.addr + (y * data.line_length + x * (data.bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void            drow_line(t_data data, int current_x, int startY, int endY, int color)
{
    char    *dst;
    while (startY < endY)
    {
        dst = data.addr + (startY * data.line_length + current_x * (data.bits_per_pixel / 8));
        *(unsigned int*)dst = color;
        startY++;
    }
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
                player->posX = j;
                player->posY = i;
                break;
            }
            j++;
        }
        i++;
        j = 0;
    }
    (player->direct == 'N') ? player->rotation_angle = M_PI * 3 / 2 : -1;
    (player->direct == 'S') ? player->rotation_angle = M_PI / 2 : -1 ;
    (player->direct == 'W') ? player->rotation_angle = M_PI : -1;
    (player->direct == 'E') ? player->rotation_angle = 0 : -1;
}

static void ft_set_pos_player(t_game *game)
{
    if(game->player.direct == -1)
        error(-1, 'P', game);
	if (game->player.direct == 'N')
	{
		game->player.dirY = -1;
		game->player.planeX = FOV;
	}
	else if (game->player.direct == 'S')
	{
		game->player.dirY = 1;
		game->player.planeX = -FOV;
	}
	else if (game->player.direct == 'W')
	{
		game->player.dirX = -1;
		game->player.planeY = -FOV;
	}
	else if (game->player.direct == 'E')
	{
		game->player.dirX = 1;
		game->player.planeY = FOV;
	}
}
void init_struct(t_game *game)
{
    t_player player;

    player.dirX = 0;
    player.dirY = 0;
    player.planeX = 0;
    player.planeY = 0;

    mlx_get_screen_size(&game->mlx.monitor_width, &game->mlx.monitor_hight);
    parser(game, game->mlx.file);
    get_pos(&player, game);
    game->player = player;
    ft_set_pos_player(game);
    init(game);
    game->data.img = mlx_new_image(game->mlx.mlx, game->mlx.win_width, game->mlx.win_hight);
    game->data.addr = mlx_get_data_addr(game->data.img, &game->data.bits_per_pixel, &game->data.line_length,
                                 &game->data.endian); 
}