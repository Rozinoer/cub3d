#include "cub3d.h"
#define FOV 0.5

static void get_pos(t_player *player, t_game *game)
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
    (player->direct == 'N') ? player->posX += 0.5: -1;
    (player->direct == 'S') ? player->posX += 0.5 : -1;
    (player->direct == 'W') ? player->posY += 0.5 : -1;
    (player->direct == 'E') ? player->posY += 0.5 : -1;
}

static void ft_set_pos_player(t_game *game)
{
    if(game->player.direct == -1)
        ft_error("Error. Player position not found\n");
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

static int init_window(t_game *game)
{
    game->mlx.mlx = mlx_init();
    game->mlx.mlx_win = mlx_new_window(game->mlx.mlx, game->mlx.win_width, game->mlx.win_hight, "cub3d");
    return (0);
}

static int init(t_game *game)
{
    init_window(game);
    return (0);
}

void init_struct(t_game *game)
{
    t_player player;

    player.dirX = 0;
    player.dirY = 0;
    player.planeX = 0;
    player.planeY = 0;
    player.direct = -1;
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