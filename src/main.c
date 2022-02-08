#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>

#include "constante.h"
#include "map.h"
#include "player.h"
#include "play.h"
#include "bomb.h"
//#include "thread_play.h"


int main(void)
{
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	SDL_Init(SDL_INIT_VIDEO);

	//Init window and renderer
	if(SDL_CreateWindowAndRenderer(SIZE_WINDOW_W, SIZE_WINDOW_H,0, &window, &renderer) != 0)
		fprintf(stderr, "Impossible de creer la fenetre et le rendu\n");
	
	//Init map
	block* b = block_create(renderer);
	read_level(b);
	//Init Player
	player* p = player_create(renderer, PLAYER_START_POS_X, PLAYER_START_POS_Y);
	//Init Bomb
	bomb* boom = bomb_create(renderer);
	//Init input
	input_keys in;
	input_key_init(&in);
	//Init thread
	SDL_Thread* thread_boom;
	bomber b_t;
	bomber_init(&b_t, renderer, &in, boom, b, p);
	thread_boom = SDL_CreateThread(bomb_thread, "bomb_thread", &b_t);
	if(thread_boom == NULL)
		fprintf(stderr, "Impossible de créer le thread bomber\n");

	while(in.quit)
	{
		update_event(&in, p, b, boom);	

		SDL_RenderClear(renderer);

		//display map	
		block_display(renderer, b);
	
		//display  player
		player_display(renderer,p);

		//display bom TEMPORAIRE
		bomb_display(renderer, boom);


		SDL_RenderPresent(renderer);
	}

	//liberation
	block_destroy(b);
	player_destroy(p);
	bomb_destroy(boom);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	return EXIT_SUCCESS;
}
