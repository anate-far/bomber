#ifndef PLAY_H
#define PLAY_H

#include "player.h"
#include "map.h"
#include "bomb.h"

//play
typedef struct{
	SDL_bool key[SDL_NUM_SCANCODES];
	SDL_bool quit;	
}input_keys;


void input_key_init(input_keys* in);
void update_event(input_keys* in, player* p, block* b, bomb* boom);

//thread
typedef struct{
	SDL_Renderer* renderer;
	bomb* boom;
	player* p;
	input_keys* in;
	block* b;

}bomber;



void bomber_init(bomber* boom_t, SDL_Renderer* _renderer, input_keys* _in, bomb* _boom, block* _b, player* _p);
int bomb_thread(void* ptr);

#endif
