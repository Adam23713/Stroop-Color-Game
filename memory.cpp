#include "button.h"
#include "memory.h"

const int WIDTH = 800;
const int HEIGHT = 600;
const int BBP = 32;

SDL_Surface *screen = NULL;

int main(int argc, char* argv[])
{
	bool sound = true;
	int value;
	char s_exit[] = "Kilépés";
	char sgame1[] = "Színagyaló";
	SDL_Color colors[7];
	colors[0].r = colors[0].g = colors[0].b = 255; //White
	colors[1].r = colors[1].g = colors[1].b = 0; //Black
	colors[2].r = 29; colors[2].g = 71; colors[2].b = 209; //Blue
	colors[3].r = 29; colors[3].g = 209; colors[3].b = 37; //Green
	colors[4].r = 209; colors[4].g = 29; colors[4].b = 37; //Red
	colors[5].r = 29; colors[5].g = 209; colors[5].b = 37; //Yellow
	colors[6].r = 134; colors[6].g = 14; colors[6].b = 127; //Purple
	SDL_Surface *background = NULL;
	TTF_Font *font1 = NULL;
	SDL_Event event;
	
	if(init(&sound) == false)
	{
		fputs("Kérem lépjen kapcsolatba a készítővel:\nkerteszadam23@gmail.com\n",stderr);
		return EXIT_FAILURE;
	}
	background = optimalize("data/images/backgrounds/backg1.jpg");
	SDL_BlitSurface(background, NULL, screen, NULL);
	font1 = TTF_OpenFont("data/fonts/AlegreyaSans-Regular.otf", 28);
	if(font1 == NULL)
	{
		fputs("Hibba!\nNem lehet megnyitni a AlegreyaSans-Regular.otf fájlt!\n",stderr);
		fputs("Kérem lépjen kapcsolatba a készítővel:\nkerteszadam23@gmail.com\n",stderr);
		return EXIT_FAILURE;
	}
	
	//Buttons init
	//Exit button
	Button exit_button(640,540,160,60,"data/images/buttons/exit0.png","data/images/buttons/exit1.png");
	exit_button.set_id(1);
	exit_button.title(font1,s_exit,colors[0]);
	exit_button.title_pos(15,10);
	if(sound == true)
	{
		exit_button.over_sound_effect("data/sounds/button.wav");
		exit_button.push_sound_effect("data/sounds/button.wav");
	}
	//Game 1 button
	Button game1_button(20,40,160,60,"data/images/buttons/button1.png","data/images/buttons/button2.png");
	game1_button.set_id(6);
	game1_button.title(font1,sgame1,colors[0]);
	game1_button.title_pos(15,10);
	if(sound == true)
	{
		game1_button.over_sound_effect("data/sounds/button.wav");
		game1_button.push_sound_effect("data/sounds/button.wav");
	}
	
	//Cycle
	while(SDL_WaitEvent(&event))
	{
		if(event.type == SDL_QUIT)
			break;
		if(event.type == SDL_KEYDOWN)
			if(event.key.keysym.sym == SDLK_ESCAPE)
				break;

		exit_button.handle_events(event);
		exit_button.show(screen);
		game1_button.handle_events(event);
		game1_button.show(screen);
		if(exit_button.get_push())
		{
			break;
		}
		if(game1_button.get_push())
		{
			game1_button.set_push(false);
			value = game_1(font1,sound);
			if(value == 1)
				break;
			SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,0,0,0));
			SDL_BlitSurface(background, NULL, screen, NULL);
			exit_button.show(screen);
			game1_button.show(screen);
		}
		SDL_Flip(screen);
	}
	
	SDL_FreeSurface(background);
	TTF_CloseFont(font1);
	TTF_Quit();
	SDL_Quit();
	return EXIT_SUCCESS;
}

bool init(bool *sound)
{
	if((SDL_Init(SDL_INIT_EVERYTHING)) == -1)
	{
		fputs("Hiba: Nem lehet inicializálni az SDL-t!\n",stderr);
		return false;
	}
		
	if((screen = SDL_SetVideoMode(WIDTH,HEIGHT,BBP,SDL_SWSURFACE)) ==NULL)
	{
		fputs("Hiba: Nem hozható létre a képernyő!\nHiba az SDL inicializálása közben!\n",stderr);
		return false;
	}
			
	 SDL_WM_SetCaption( "Fejlesztő Játék", NULL );
	 
	if(TTF_Init() == -1)
	{
		fputs("Hiba a fontok inicializálása közben!\n",stderr);
		return false;
	}
	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
	{
		fputs("Hiba: Hangok lejátszása nem lehetséges!\n",stderr);
		*sound = false;
	}
    
	 
	 return true;
}
