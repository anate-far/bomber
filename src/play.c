#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#include "tools_sdl.h"
#include "player.h"
#include "bomb.h"
#include "constante.h"
#include "play.h"
#include "map.h"


void input_key_init(input_keys* in)
{
	for(int i = 0; i <= SDL_NUM_SCANCODES; i++)
		in->key[i] = SDL_FALSE;
	in->quit = SDL_TRUE;	
}

void update_event(input_keys* in, player* p, block* b, bomb* boom)
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_QUIT:
				in->quit = SDL_FALSE;
				break;
			
			case SDL_KEYDOWN:
				in->key[event.key.keysym.scancode] = SDL_TRUE;
				break;
			case SDL_KEYUP:
				in->key[event.key.keysym.scancode] = SDL_FALSE;
				break;

		}

	}
	//quit
	if(in->key[SDL_SCANCODE_ESCAPE])
	in->quit = SDL_FALSE;
	
	//move
	if(! p->is_dead)
	{
		if(in->key[SDL_SCANCODE_UP])
			player_move(p,b,UP);
		
		if(in->key[SDL_SCANCODE_DOWN])
			player_move(p,b,DOWN);
		
		if(in->key[SDL_SCANCODE_LEFT])
			player_move(p,b,LEFT);
		
		if(in->key[SDL_SCANCODE_RIGHT])
			player_move(p,b,RIGHT);
	}

	//place bomb
	if(in->key[SDL_SCANCODE_SPACE])
	{
		if(! p->is_dead)
		{
			place_bomb(boom, p);	
			boom->is_visible = SDL_TRUE;
		}
	}
	SDL_Delay(50);
}


//thread
void bomber_init(bomber* boom_t, SDL_Renderer* _renderer, input_keys* _in, bomb* _boom, block* _b, player* _p)
{
	boom_t->renderer = _renderer;
	boom_t->boom = _boom;
	boom_t->in = _in;
	boom_t->b = _b;
	boom_t->p = _p;
}

int bomb_thread(void* ptr)
{
	bomber* boom_t = ptr;

	while(boom_t->in->quit)
	{
		if(boom_t->boom->is_visible)
		{
			bomb_explosion(boom_t->boom, boom_t->b, boom_t->p);
			boom_t->boom->is_visible = SDL_FALSE;
		}
	}	

	return 0;
}
