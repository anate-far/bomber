#ifndef MAP_H
#define MAP_H

typedef struct{
	int * block;
	SDL_Texture* texture_wall;
	SDL_Texture* texture_box;
	SDL_Rect pos_block;	
}block;

//constructeur destructeur

block* block_create(SDL_Renderer* renderer);
void block_destroy(block* b);

//init
void read_level(block* b);

//display
void block_debug(block* b);
void block_display(SDL_Renderer* renderer, block* b);

//tools
int get_index_position(SDL_Rect pos);

#endif
