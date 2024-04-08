// https://rosettacode.org/wiki/Conway%27s_Game_of_Life#C
// adapted by TurBoss for ZealOS (2024)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#include "zos_errors.h"
#include "zos_vfs.h"
#include "zos_sys.h"
#include "zos_video.h"

#define WIDTH 80
#define HEIGHT 40

#define for_x for (int x = 0; x < WIDTH; x++)
#define for_y for (int y = 0; y < HEIGHT; y++)
#define for_xy for_x for_y



void show(void *u) {
	bool (*univ)[WIDTH] = u;
	for_y {
		for_x printf(univ[y][x] ? "@" : " ");
		printf("\n");
	}
	zos_video_cmd_t CMD_CLEAR_SCREEN;
}


void evolve(void *u)
{
	bool (*univ)[WIDTH] = u;
	bool new[HEIGHT][WIDTH];

	for_y for_x {
		int n = 0;

		for (int y1 = y - 1; y1 <= y + 1; y1++)
			for (int x1 = x - 1; x1 <= x + 1; x1++)
				if (univ[(y1 + HEIGHT) % HEIGHT][(x1 + WIDTH) % WIDTH])
					n++;

		if (univ[y][x]) n--;

		new[y][x] = (n == 3 || (n == 2 && univ[y][x]));
	}

	for_y for_x univ[y][x] = new[y][x];
}


void game() {

	bool univ[HEIGHT][WIDTH];

	for_xy univ[y][x] = rand() < RAND_MAX / 5 ? 1 : 0;

	while (1) {
		show(univ);
		evolve(univ);
	}
}

int main(int argc, char** argv) {

	game();

	return 0;
}

