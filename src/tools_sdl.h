#ifndef TOOLBASE_H
#define TOOLBASE_H

#include<SDL.h>

void clearRessources(const char *message, SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture);

SDL_Texture* create_texture(SDL_Renderer* renderer, const char* name_img);

void stop_to_time(double time_s);

#endif
