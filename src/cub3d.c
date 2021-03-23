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
    mlx_destroy_image(game->mlx.mlx, game->data.img);
    game->data.img = mlx_new_image(game->mlx.mlx, game->mlx.win_width, game->mlx.win_hight);
    game->data.addr = mlx_get_data_addr(game->data.img, &game->data.bits_per_pixel, &game->data.line_length,&game->data.endian);


    mlx_hook(game->mlx.mlx_win, 2, 1L<<0, key_pressed, game);
    render_next_frame(game);
    if (game->save == 1)
        screenshot(game);
    
    return (0);
}

static void check_expansion(char *str)
{
    int len;

    len = ft_strlen(str);
    str = str + (len - 4);
    if (ft_strncmp(str, ".cub", 4) != 0)
        ft_error("Error. Map file haves bad expansion\n");
}

int main(__unused int args, char **argv)
{
    t_game game;

    if (args == 2 || args == 3)
    {
        check_expansion(argv[1]);
        game.mlx.file = argv[1];
        init_struct(&game);
        if (args == 3 && (ft_strncmp(argv[2], "--save", 6) == 0))
			game.save = 1;
		else if (args == 3)
			ft_putstr("Error arg 2 is not correct\n");
		else
			game.save = 0;
        mlx_loop_hook(game.mlx.mlx, update, &game);
        mlx_loop(game.mlx.mlx);
    }
    else
        write(2, "Error: wrong number of arguments\n", 26);
    return (0);
}