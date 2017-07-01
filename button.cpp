#include "button.h"
//Button 0.6
//Írta: Kertész Ádám

int Button::count = 0;

Button::Button(int x, int y, int w, int h, const char *path1, const char *path2)
{
	id = ++count;
	message_offset.x = box.x = x;
	message_offset.y = box.y = y;
	box.w = w;
	box.h = h;
	over_sound = false;
	push_sound = false;
	over = false;
	gone = false;
	push = false;
	bool_message = false;
	message = NULL;
	over_effect = NULL;
	push_effect = NULL;
	ButtonSkin_1 = optimalize(path1);
	ButtonSkin_2 = optimalize(path2);
	
}

Button::~Button()
{
	if(message != NULL)
		SDL_FreeSurface(message);
	if(over_effect != NULL)
		Mix_FreeChunk(over_effect);
	if(push_effect != NULL)
		Mix_FreeChunk(push_effect);
	SDL_FreeSurface(ButtonSkin_1);
	SDL_FreeSurface(ButtonSkin_2);
}

void Button::show(SDL_Surface *screen)
{
	//Show the button
	if(over == false)
		SDL_BlitSurface( ButtonSkin_1, NULL, screen, &box );
	else if(over == true)
		SDL_BlitSurface( ButtonSkin_2, NULL, screen, &box );
	if(bool_message == true)
		 SDL_BlitSurface(message,NULL,screen,&message_offset);
}

void Button::set_push(bool var)
{
	push = var;
}

bool Button::get_push()
{
	return push;
}


//External function
SDL_Surface* optimalize(const char *titles)
{
	SDL_Surface* optimizedImage = NULL;
    SDL_Surface* tempB = NULL;
    
    tempB = IMG_Load(titles);
    //Load Pictures
    if( tempB != NULL )
    {
        optimizedImage = SDL_DisplayFormat(tempB);
        SDL_FreeSurface(tempB);
     }
     else
	{
		exit(1);
		puts("Nincs ilyen fájl!");
	}
	
	Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0, 0, 0 );
	SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
	 
	return optimizedImage;
    
}
//=======================================================7

void Button::handle_events(SDL_Event event0)
{
	
	//The mouse offsets
	int x = 0;
	int y = 0;

	//If the mouse moved
	if( event0.type == SDL_MOUSEMOTION )
	{
		//Get the mouse offsets
		x = event0.motion.x;
		y = event0.motion.y;

		//If the mouse is over the button
		if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) )
		{
			over=true;
			if(gone==true)
			{
				if(over_sound == true)
				{
					if(Mix_PlayChannel(-1,over_effect,0) == -1)
					{
						over_sound = false;
					}
				}
				gone=false;
			}
		}
		//If not
		else
		{
			over=false;
			gone=true;
		}
	}
		
	 //If a mouse button was pressed
	if( event0.type == SDL_MOUSEBUTTONDOWN )
	{
		//If the left mouse button was pressed
		if( event0.button.button == SDL_BUTTON_LEFT )
		{
			//Get the mouse offsets
			x = event0.button.x;
			y = event0.button.y;

			//If the mouse is over the button
			if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) )
			{
				if(push == false)
					push = true;
				else if(push == true)
					push = false;
					
				if(push_sound == true)
				{
					if(Mix_PlayChannel(-1,push_effect,0) == -1)
					{
						push_sound = false;
					}
				}
			}
		}
	}
}

void Button::change_skin(const char *path1, const char *path2)
{
	ButtonSkin_1 = optimalize(path1);
	ButtonSkin_2 = optimalize(path2);
}

void Button::title(TTF_Font *font, const char *sname, SDL_Color textcolor)
{
	strcpy(name,sname);
	message = TTF_RenderUTF8_Blended(font, name, textcolor); 
	bool_message = true;
}

void Button::title_pos(int x, int y)
{		
	message_offset.x += x;
	message_offset.y += y;
	
	if(x >= box.w || x < 0)
		message_offset.x = box.x;
	if(y >= box.h || y < 0)
		message_offset.y = box.y;
}

void Button::over_sound_effect(const char *path)
{
	over_effect = Mix_LoadWAV(path);
	over_sound = true;
}

void Button::push_sound_effect(const char *path)
{
	push_effect = Mix_LoadWAV(path);
	push_sound = true;
}

void Button::set_over_sound(bool var)
{
	over_sound = var;
}

void Button::set_push_sound(bool var)
{
	push_sound = var;
}

void Button::set_title(bool var)
{
	bool_message = var;
}


void Button::change_pos(int x, int y)
{
	message_offset.x = box.x = x;
	message_offset.y = box.y = y;
	
}

int Button::get_id()
{
	return id;
}

void Button::set_id(int value)
{
	id = value;
}

void Button::get_title(char *text)
{
	strcpy(text,name);
}


bool Button::get_over()
{
	return over;
}


