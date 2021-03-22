#include "cub3d.h"

// static	void collusion(t_game *game, int rotSpeed, int flag)
// {
// 	if (flag == 1)
// 	{
// 		if (game->map.map[(int)(game->player.posY + game->player.dirY * rotSpeed)]
// 		[(int)(game->player.posX + game->player.dirX * rotSpeed)] != '1')
// 		{
// 			game->player.posX += game->player.dirX * rotSpeed;
//       		game->player.posY += game->player.dirY * rotSpeed;
// 		}
// 	}
// 	else
// 	{
// 		if (game->map.map[(int)(game->player.posY + game->player.dirY * rotSpeed)]
// 		[(int)(game->player.posX - game->player.dirX * rotSpeed)] != '1')
// 		{
// 			game->player.posY -= -game->player.dirX * rotSpeed;
// 			game->player.posX -= game->player.dirY * rotSpeed;
// 		}
// 	}
// }

static void another_key(int keycode, t_game *game, double oldDirX, double oldPlaneX)
{
	double rotSpeed;

	rotSpeed = 0.1;
	if (keycode == 123)
		rotSpeed *= -1;
    else if (keycode == 53)
    {
      mlx_clear_window(game->mlx.mlx, game->mlx.mlx_win);
      mlx_destroy_window(game->mlx.mlx, game->mlx.mlx_win);
      exit(0);
    }
	game->player.dirX = game->player.dirX * cos(rotSpeed) - game->player.dirY * sin(rotSpeed);
	game->player.dirY = oldDirX * sin(rotSpeed) + game->player.dirY * cos(rotSpeed);
	game->player.planeX = game->player.planeX * cos(rotSpeed) - game->player.planeY * sin(rotSpeed);
	game->player.planeY = oldPlaneX * sin(rotSpeed) + game->player.planeY * cos(rotSpeed);
}

int key_pressed(int keycode, t_game *game)
{
	double rotSpeed;
	double oldDirX;
	double oldPlaneX;
	double smooth;

	smooth = 0.4;
	oldDirX = game->player.dirX;
	oldPlaneX = game->player.planeX;
	rotSpeed = 0.1;
	if (keycode == W || keycode == S)
    {
		if (keycode == S)
		{
			rotSpeed *= -1;
			smooth *= -1;
		}
		// collusion(game, rotSpeed, 1);
		if (game->map.map[(int)(game->player.posY + game->player.dirY * (rotSpeed + smooth))]
		[(int)(game->player.posX + game->player.dirX * (rotSpeed + smooth))] != '1')
		{
			game->player.posX += game->player.dirX * rotSpeed;
      		game->player.posY += game->player.dirY * rotSpeed;
		}
		// game->player.posX += game->player.dirX * rotSpeed;
      	// game->player.posY += game->player.dirY * rotSpeed;
    }
    if (keycode == A || keycode == D)
    {
		if (keycode == A)
		{
			rotSpeed *= -1;
			smooth *= -1;
		}
		// collusion(game, rotSpeed, 2);
		if (game->map.map[(int)(game->player.posY + game->player.dirY * (rotSpeed + smooth))]
		[(int)(game->player.posX - game->player.dirX * (rotSpeed + smooth))] != '1')
		{
			game->player.posY -= -game->player.dirX * rotSpeed;
			game->player.posX -= game->player.dirY * rotSpeed;
		}
		// game->player.posY -= -game->player.dirX * rotSpeed;
		// game->player.posX -= game->player.dirY * rotSpeed;
    }
    else if (keycode == 124 || keycode == 123 || keycode == 53)
		another_key(keycode, game, oldDirX, oldPlaneX);
    return(0);
}