#include "cub3d.h"

static void another_key(int keycode, t_game *game, double oldDirX, double oldPlaneX)
{
	double rotSpeed;

	rotSpeed = 0.1;
	if (keycode == 123)
		rotSpeed *= -1;
	else if (keycode == 53)
	{
		mlx_destroy_image(game->mlx.mlx, game->data.img);
		mlx_clear_window(game->mlx.mlx, game->mlx.mlx_win);
		mlx_destroy_window(game->mlx.mlx, game->mlx.mlx_win);
		exit(0);
	}
	game->player.dirX = game->player.dirX * cos(rotSpeed) - game->player.dirY * sin(rotSpeed);
	game->player.dirY = oldDirX * sin(rotSpeed) + game->player.dirY * cos(rotSpeed);
	game->player.planeX = game->player.planeX * cos(rotSpeed) - game->player.planeY * sin(rotSpeed);
	game->player.planeY = oldPlaneX * sin(rotSpeed) + game->player.planeY * cos(rotSpeed);
	render_next_frame(game);
}

static void forward_reverse(int keycode, t_game *game)
{
	double move_speed;
	double smooth;

	smooth = 0.1;
	move_speed = 0.1;
	if (keycode == S)
	{
		move_speed *= -1;
		smooth *= -1;
	}
	if (game->map.map[(int)(game->player.posY + game->player.dirY * (move_speed + smooth))]
	[(int)(game->player.posX + game->player.dirX * (move_speed + smooth))] != '1')
	{
		game->player.posX += game->player.dirX * move_speed;
		game->player.posY += game->player.dirY * move_speed;
		render_next_frame(game);
	}
}

static void left_right(int keycode, t_game *game)
{
	double move_speed;
	double smooth;

	smooth = 0.5;
	move_speed = 0.1;
	if (keycode == A)
	{
		move_speed *= -1;
		smooth *= -1;
	}
	if (game->map.map[(int)(game->player.posY + game->player.dirY * (move_speed * game->player.planeY))]
	[(int)(game->player.posX - game->player.dirX * (move_speed * game->player.planeX))] != '1')
	{
		game->player.posY -= -game->player.dirX * move_speed;
		game->player.posX -= game->player.dirY * move_speed;
		render_next_frame(game);
	}
}

int key_pressed(int keycode, t_game *game)
{
	double oldDirX;
	double oldPlaneX;

	oldDirX = game->player.dirX;
	oldPlaneX = game->player.planeX;
	if (keycode == W || keycode == S)
	{
		forward_reverse(keycode, game);
	}
	if (keycode == A || keycode == D)
	{
		left_right(keycode, game);
	}
	else if (keycode == 124 || keycode == 123 || keycode == 53)
		another_key(keycode, game, oldDirX, oldPlaneX);
	return(0);
}