//Button 0.6
//Írta: Kertész Ádám

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include <stdio.h>
#include <string>

#ifndef BUTTON_H
#define BUTTON_H

//public image optimalize
SDL_Surface* optimalize(const char *titles);

class Button
{
	private:
	
	int id;
	bool push;
	bool gone;
	bool over;
	bool bool_message;
	bool over_sound;
	bool push_sound;
	char name[15];
	SDL_Rect box;
	SDL_Rect message_offset;
	SDL_Surface *message;
	SDL_Surface *ButtonSkin_1;
	SDL_Surface *ButtonSkin_2;	
	Mix_Chunk *over_effect;
	Mix_Chunk *push_effect;
	
	static int count;

	public:
	
	//Constructor & Destructor
	Button(int x, int y, int w, int h, const char *path1, const char *path2);
	~Button();
	
	bool get_over();
	void title(TTF_Font *font, const char *name, SDL_Color textcolor);
	void title_pos(int x, int y);
	void show(SDL_Surface *screen);
	void handle_events(SDL_Event event0);
	void change_skin(const char *path1, const char *path2);
	void change_pos(int x, int y);
	void over_sound_effect(const char *path);
	void push_sound_effect(const char *path);
	int get_id();
	void get_title(char*);
	void set_id(int value);
	void set_over_sound(bool var);
	void set_push_sound(bool var);
	void set_title(bool var);
	void set_push(bool var);
	bool get_push();
};

#endif
