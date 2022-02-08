#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>

#include "constante.h"
#include "map.h"
#include "bomb.h"
#include "play.h"
#include "player.h"
#include "bomb.h"
#include "tools_sdl.h"


//constructeur - destructeur
bomb* bomb_create(SDL_Renderer* renderer)
{
	bomb* boom = malloc(sizeof(bomb));

	//Create texture
	boom->texture_bomb = malloc(sizeof(SDL_Texture*));
		boom->texture_bomb[0] = create_texture(renderer,"img/bombT1.png");
		boom->texture_bomb[1] = create_texture(renderer,"img/bomb_invisible.png");
	//init position and size
	boom->pos_bomb.x = 128;//PLAYER_START_POS_X;
	boom->pos_bomb.y = 64;//PLAYER_START_POS_Y;
	boom->pos_bomb.w = BOMB_SIZE_W;
	boom->pos_bomb.h = BOMB_SIZE_H; 

	for(int i = 0; i < 2; i++)
		SDL_QueryTexture(boom->texture_bomb[i], NULL, NULL, &boom->pos_bomb.w, &boom->pos_bomb.h);

	boom->is_visible = SDL_FALSE;
	
	boom->damage = 1;

	return boom;	
}
void bomb_destroy(bomb* boom)
{
	for(int i = 0; i < 2; i++)
		SDL_DestroyTexture(boom->texture_bomb[i]);

	free(boom->texture_bomb);
	free(boom);
}

//display

void place_bomb(bomb* boom, player* p)
{
	boom->pos_bomb.x = p->pos_body.x;
	boom->pos_bomb.y = p->pos_body.y;
}

void bomb_display(SDL_Renderer* renderer, bomb* boom)
{
	if(boom->is_visible)
		SDL_RenderCopy(renderer, boom->texture_bomb[0], NULL, &boom->pos_bomb);
	else
		SDL_RenderCopy(renderer, boom->texture_bomb[1], NULL, &boom->pos_bomb); 
}


//dammage
void bomb_explosion(bomb* boom, block* b, player* p)
{
	int index;
	SDL_Delay(1000);

	//degat au joueur
	bomb_set_damage(boom, p);

	printf("life : %d\n", p->health);

	//explosion des block
	index = get_index_position(boom->pos_bomb);
	//check axe y
	if(b->block[index - NB_BLOCK_X] == BOX_BLOCK) // UP
		b->block[index - NB_BLOCK_X] = 0;
	if(b->block[index + NB_BLOCK_X] ==  BOX_BLOCK) // DOWN
		b->block[index + NB_BLOCK_X] = 0;
	//check axe x
	if(b->block[index - 1] == BOX_BLOCK) // LEFT
		b->block[index - 1] = 0;
	if(b->block[index + 1] == BOX_BLOCK) // RIGHT
		b->block[index + 1] = 0;

	p->is_invinsible = SDL_FALSE;

}
//gerer les dégat fait au joueur
void bomb_set_damage(bomb* boom, player* p)
{
	for(int i =0; i < 3; i ++)
	{	
		//UP
		if((boom->pos_bomb.y - i * 64 == p->pos_body.y) && (boom->pos_bomb.x == p->pos_body.x))
			player_remove_life(p, boom->damage);
		//DOWN
		if((boom->pos_bomb.y + i * 64 == p->pos_body.y) && (boom->pos_bomb.x == p->pos_body.x))
			player_remove_life(p, boom->damage);
		//LEFT
		if((boom->pos_bomb.x - i * 64 == p->pos_body.x) && (boom->pos_bomb.y == p->pos_body.y))
			player_remove_life(p, boom->damage);
		//RIGHT
		if((boom->pos_bomb.x + i * 64 == p->pos_body.x) && (boom->pos_bomb.y == p->pos_body.y))
			player_remove_life(p, boom->damage);
	}
}
