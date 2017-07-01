#include "button.h"
#include "memory.h"
#include <stdlib.h>

extern SDL_Surface *screen;

void end_game(TTF_Font *font1)
{
	SDL_Event event;
	SDL_Surface *back = NULL;
	
	back = optimalize("data/images/backgrounds/endtable.jpg");
	
	//Exit button
	Button exit_button(640,540,165,55,"data/images/buttons/button1.png","data/images/buttons/button2.png");
	exit_button.set_id(14);
	exit_button.title(font1,"OK",colors[0]);
	exit_button.title_pos(15,10);
	
	while(SDL_WaitEvent(&event))
	{
		if(exit_button.get_push())
			break;
	}
	
	
	SDL_FreeSurface(back);
	return;
}
