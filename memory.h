#ifndef MEMORY_H
#define MEMORY_H

#include "button.h"

bool init(bool*);
void mix_colors();
SDL_Surface* LoadWallpaper(const char *titles);
void settings(TTF_Font *font,TTF_Font *font2, SDL_Color *colors, int *time, char *player_name);
void sound_load(Button*,Button*,Button*,Button*,Button*,Button*,bool);
void drawn(TTF_Font*,SDL_Color*,Button*,Button*,Button*,Button*,Button*,const int*,const char**,const int*);
int game_1(TTF_Font*,bool);
void search(char *text, char *color, Button *blue, Button *green, Button *red, Button *yellow, int *t1_color, int *t2_color);
void end_game(TTF_Font *font1);

#endif
