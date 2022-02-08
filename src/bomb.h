#ifndef BOMB_H
#define BOMB_H

#include "player.h"

typedef struct{
	SDL_Texture** texture_bomb;
	SDL_Rect pos_bomb;
	SDL_bool is_visible;
	int damage;
}bomb;

//constructeur - destructeur
bomb* bomb_create(SDL_Renderer* renderer);
void bomb_destroy(bomb* boom);

//display
void place_bomb(bomb* boom, player* p);
void bomb_display(SDL_Renderer* renderer, bomb* boom);

//dammage
void bomb_explosion(bomb* boom, block* b, player* p);
//gere les dégats fait au joueurs 
void bomb_set_damage(bomb* boom, player* p);

#endif
