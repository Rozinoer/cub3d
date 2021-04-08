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
    if(player->direct != -1)
    {
        player->posX += 0.5;
        player->posY += 0.5;
    }
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

static t_data		*ft_create_img_txtr(char *file, void *ptr_mlx)
{
	t_data	*txtr;

	if (!(txtr = malloc(sizeof(t_data))))
		ft_error("Error memory allocation\n");
	txtr->img = mlx_xpm_file_to_image(ptr_mlx, file, \
							&txtr->width, &txtr->height);
	if (!txtr->img)
		ft_error("Error map: error texture\n");
	txtr->addr = mlx_get_data_addr(txtr->img, &txtr->bits_per_pixel, \
							&txtr->line_length, &txtr->endian);
	return (txtr);
}

static int init(t_game *game)
{
    game->mlx.mlx = mlx_init();
    game->mlx.mlx_win = mlx_new_window(game->mlx.mlx, game->mlx.win_width, game->mlx.win_hight, "cub3d");
    game->txtr.wall_n = ft_create_img_txtr(game->map.no_tex, game->mlx.mlx);
	game->txtr.wall_s = ft_create_img_txtr(game->map.so_tex, game->mlx.mlx);
	game->txtr.wall_e = ft_create_img_txtr(game->map.ea_tex, game->mlx.mlx);
	game->txtr.wall_w = ft_create_img_txtr(game->map.we_tex, game->mlx.mlx);
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