#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>

#include "tools_sdl.h"
#include "map.h"
#include "constante.h"
#include "tools.h"
#include "play.h"



block* block_create(SDL_Renderer* renderer)
{
	block* b = malloc(sizeof(block));

	//Create texture
	b->texture_box = create_texture(renderer, "img/box.png");
	b->texture_wall = create_texture(renderer, "img/wall.png");
	//init position and size
	b->pos_block.x = 0;
	b->pos_block.y = 0;
	b->pos_block.w = BLOCK_SIZE_W;
	b->pos_block.h = BLOCK_SIZE_H;

	SDL_QueryTexture(b->texture_wall, NULL, NULL, &b->pos_block.w, &b->pos_block.h);
	SDL_QueryTexture(b->texture_box, NULL, NULL, &b->pos_block.w, &b->pos_block.h);

	//init tab2D for map 
	b->block = malloc(sizeof(int) * MAP_TAB_SIZE);
	for(int i = 0; i < MAP_TAB_SIZE; i ++)
	{
		b->block[i] = i;
	}


	return b;
}


void block_destroy(block* b)
{
	SDL_DestroyTexture(b->texture_wall);
	SDL_DestroyTexture(b->texture_box);

	free(b->block);
	free(b);
}

//init

void read_level(block* b)
{
	FILE* level = fopen("level_test.txt", "r");
	if(level == NULL)
		fprintf(stderr, "Impossible d'ouvrire le fichier\n");

	for(int i = 0; i < MAP_TAB_SIZE; i++)
	{
		char c = fgetc(level);

		if(c == 10)
			c = fgetc(level);

		 int value = char_to_int(c);
		 b->block[i] = value;
	}

	fclose(level);
}

//display
void block_debug(block* b)
{
	int x = 0;
	for(int i = 0;i < MAP_TAB_SIZE; i++)
	{	
		if(x == NB_BLOCK_X)
		{
			fprintf(stderr, "\n");
			x = 0;
		}

		x++;
		fprintf(stderr, "%d", b->block[i]);
	}
	fprintf(stderr,"\n\n");

}



void block_display(SDL_Renderer* renderer, block* b)
{
	int x = 0, y = 0;
	for(int i = 0; i < MAP_TAB_SIZE; i++)
	{
		if(x == NB_BLOCK_X)
		{
			x = 0;
			y++;
		}
		b->pos_block.x = BLOCK_SIZE_W * x;
		b->pos_block.y = BLOCK_SIZE_H * y;

		switch(b->block[i])
		{
			case BOX_BLOCK:
				SDL_RenderCopy(renderer,b->texture_box, NULL, &b->pos_block);
				break;
			case WALL_BLOCK:
				SDL_RenderCopy(renderer,b->texture_wall, NULL, &b->pos_block);
				break;
				
		}

		x++;
	}
}

//tools
int get_index_position(SDL_Rect pos)
{	
	//calule de l'index du tableau block 
	int x = pos.x / 64;
	int y = pos.y / 64;

	int index = (y * NB_BLOCK_X) + x; // f = (y * Mx) + x

	return index;
}
