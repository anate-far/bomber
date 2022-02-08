#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>

#include "tools_sdl.h"
#include "constante.h"
#include "tools.h"
#include "player.h"
#include "map.h"


//constructeur -destructeur
player* player_create(SDL_Renderer* renderer, int x, int y)
{
	player* p = malloc(sizeof(player));

	//Create texture
	p->texture_body = create_texture(renderer, "img/player1/idle/test1.png");
	//init position and size
	p->pos_body.x = x;
	p->pos_body.y = y;
	p->pos_body.w = PLAYER_SIZE_W;
	p->pos_body.h = PLAYER_SIZE_H;

	SDL_QueryTexture(p->texture_body, NULL, NULL, &p->pos_body.w, &p->pos_body.h);

	p->speed = WALK_SPEED;

	//Star healt player
	p->health = player_set_life(START_HEALTH);
	p->is_invinsible = SDL_FALSE;
	p->is_dead = SDL_FALSE;

	return p;
}
void player_destroy(player* p)
{
	SDL_DestroyTexture(p->texture_body);

	free(p);
}


//Display
void player_display(SDL_Renderer* renderer, player* p)
{
	SDL_RenderCopy(renderer, p->texture_body, NULL, &p->pos_body);
}

void player_debug_pos(player* p)
{
	fprintf(stderr, "pos x : %d\n", p->pos_body.x);
	fprintf(stderr, "pos y : %d\n", p->pos_body.y);
}

//move
void player_move(player* p, block* b, int movement)
{
	int index;
	switch(movement)
	{
		case UP:
			index = get_index_position(p->pos_body);
			//Calcule si il y a un block au dessu
			if((b->block[index - NB_BLOCK_X] == WALL_BLOCK) || (b->block[index - NB_BLOCK_X] == BOX_BLOCK))
				p->pos_body.y -= 0;
			else	
				p->pos_body.y -= p->speed;
			break;
		case DOWN:
			index = get_index_position(p->pos_body);
			//Calcule si il y a un block au dessou
			if((b->block[index + NB_BLOCK_X] == WALL_BLOCK) || (b->block[index + NB_BLOCK_X] == BOX_BLOCK))
				p->pos_body.y += 0;
			else	
				p->pos_body.y += p->speed;	
			break;
		case LEFT:
			index = get_index_position(p->pos_body);
			//Calcule si il y a un block sur la gauche
			if((b->block[index - 1] == WALL_BLOCK) || (b->block[index - 1] == BOX_BLOCK))
				p->pos_body.x -= 0;
			else	
				p->pos_body.x -= p->speed;
			break;
		case RIGHT:
			index = get_index_position(p->pos_body);
			//Calcule si il y a un block sur la droite
			if((b->block[index + 1] == WALL_BLOCK) || (b->block[index + 1] == BOX_BLOCK))
				p->pos_body.x += 0;
			else	
				p->pos_body.x += p->speed;
			break;
	}
}

//live
int player_set_life(int life)
{
	return life;		
}

void player_remove_life(player* p,int life)
{
	if(p->health <= 0)
	{
		p->is_dead = SDL_TRUE;
		p->health = 0;
	}

	if(! p->is_invinsible)
		p->health -= life;
	
	p->is_invinsible = SDL_TRUE;
}

