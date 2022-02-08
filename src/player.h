#ifndef PLAYER_H
#define PLAYER_H

#include "map.h"

typedef struct{
	SDL_Texture* texture_body;
	SDL_Rect pos_body;
	int speed;
	int health;
	SDL_bool is_invinsible;
	SDL_bool is_dead;
}player;

//constructeur - destructeur
player* player_create(SDL_Renderer* renderer, int x, int y);
void player_destroy(player* p);

//display
void player_display(SDL_Renderer* renderer, player* p);
void player_debug_pos(player* p);

//move
void player_move(player* p, block* b, int movement);

//live
int player_set_life(int life);
void player_remove_life(player* p, int life);
#endif
