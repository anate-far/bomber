#ifndef CONSTANTE_H
#define CONSTANTE_H

//Window
#define SIZE_WINDOW_W 960
#define SIZE_WINDOW_H 832

//Map
#define AIR_BLOCK 0
#define WALL_BLOCK 3
#define BOX_BLOCK 1

#define NB_BLOCK_X 15
#define NB_BLOCK_Y 13
#define MAP_TAB_SIZE NB_BLOCK_Y * NB_BLOCK_X

//Wall
#define BLOCK_SIZE_W 64
#define BLOCK_SIZE_H 64

//Player
#define PLAYER_SIZE_W 124
#define PLAYER_SIZE_H 189

#define PLAYER_START_POS_X 64
#define PLAYER_START_POS_Y 64
#define START_HEALTH 3

enum {UP, DOWN, LEFT, RIGHT};
#define WALK_SPEED 64
#define STOP_SPEED 0

//Bomb
#define BOMB_SIZE_W 64
#define BOMB_SIZE_H 64

#endif
