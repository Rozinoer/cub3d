#include "cub3d.h"

int key_pressed(int keycode, t_game *game)
{
	if (keycode == W) {
		game->player.walk_dir = 1;
	}
	else if (keycode == S) {
		game->player.walk_dir = -1;
	}
	else if (keycode == D) {
		game->player.turn_dir = 1;
	}
	else if (keycode == A) {
		game->player.turn_dir = -1;
	}
    printf("key[%d] was pressed\n", keycode);
	return (0);
}

int key_released(int keycode, t_game *game)
{
	if (keycode == W)
		game->player.walk_dir = 0;
	else if (keycode == S)
		game->player.walk_dir = 0;
	else if (keycode == D)
		game->player.turn_dir = 0;
	else if (keycode == A)
		game->player.turn_dir = 0;
    printf("key[%d] was unpressed\n", keycode);
	return (0);
}