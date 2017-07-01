#include "button.h"
#include "memory.h"
#include <sstream>
#include <stdlib.h>
#include <time.h>

extern SDL_Surface *screen;

int place_blue,place_green,place_red,place_yellow;
int cplace_blue,cplace_green,cplace_red,cplace_yellow;
int good_button;

int game_1(TTF_Font *font1,bool sound)
{
	SDL_Event event;
	FILE *out = NULL;
	bool quit = false;
	bool push = false;
	int points = 0;
	int max_time = 15;
	char s_points[10];
	char player_name[30];
	srand(time(NULL));
	SDL_Surface *backg = NULL;
	SDL_Surface *message1 = NULL;
	SDL_Surface *message2 = NULL;
	SDL_Surface *name_surface = NULL;
	SDL_Surface *time_message = NULL;
	SDL_Surface *point_message = NULL;
	SDL_Surface *point_surface = NULL;
	SDL_Rect offset1;
	SDL_Rect offset2;
	SDL_Rect t_offset;
	SDL_Rect time_offset;
	const char *s_color[] = {"Piros","Zöld","Kék","Sárga"};
	SDL_Color colors[7];
	colors[0].r = colors[0].g = colors[0].b = 255; //White
	colors[1].r = colors[1].g = colors[1].b = 0; //Black
	colors[2].r = 29; colors[2].g = 71; colors[2].b = 209; //Blue
	colors[3].r = 29; colors[3].g = 209; colors[3].b = 37; //Green
	colors[4].r = 209; colors[4].g = 29; colors[4].b = 37; //Red
	colors[5].r = 29; colors[5].g = 209; colors[5].b = 37; //Yellow
	colors[6].r = 134; colors[6].g = 14; colors[6].b = 127; //Purple
	
	int exit_value = 0;
	int t1_color,t2_color;
	char text[15];
	char color_text[15];
	const int color_pos[4] = {47,50,55,45};
	const int positions[4] = {65, 235, 405, 575};
	TTF_Font *font2 = TTF_OpenFont("data/fonts/Cowboy_Hippie_Pro.otf", 45);
	TTF_Font *font3 = TTF_OpenFont("data/fonts/AlegreyaSans-Bold.otf", 28);
	TTF_Font *font4 = TTF_OpenFont("data/fonts/xirwen3U.ttf",28);
	
	backg =  optimalize("data/images/backgrounds/game1.jpg");
	SDL_BlitSurface(backg,NULL,screen,NULL);
	SDL_Flip(screen);
	
	
	//Settings
	settings(font1,font2,colors,&max_time,player_name);
	
	//Fájl megnyitása ha létezik és létrehozása ha nem
	if((out = fopen("adatok.xlm","r")) != NULL)
	{
		fclose(out);
		if((out = fopen("adatok.xlm","a")) == NULL)
			fputs("Hiba a fájl megnyitásakor!",stderr);
	}
	else
	{
		if((out = fopen("adatok.xlm","a+")) == NULL)
			fputs("Hiba a fájl megnyitásakor!",stderr);
		fprintf(out,"Név\tPontok\tKapott idő\n");
	}
		
	
	SDL_BlitSurface(backg,NULL,screen,NULL);
	SDL_Flip(screen);
	
	time_message = TTF_RenderUTF8_Blended( font2,"IDŐ :", colors[6] );
	t_offset.x = 20;
	t_offset.y = 543;
	SDL_BlitSurface(time_message,NULL,screen,&t_offset);
	
	time_message = TTF_RenderUTF8_Blended( font2,"Pontok :", colors[6] );
	t_offset.x = 330;
	t_offset.y = 543;
	SDL_BlitSurface(time_message,NULL,screen,&t_offset);
	t_offset.x = 460;
	t_offset.y = 539;
	
	//Name button
	Button name_button(0,0,220,55,"data/images/buttons/namebutton.png","data/images/buttons/namebutton.png");
	name_button.set_id(13);
	name_button.title(font4,player_name,colors[6]);
	name_button.title_pos(3,7);

	
	//Back button
	Button exit_button(640,540,165,55,"data/images/buttons/back1.png","data/images/buttons/back2.png");
	exit_button.set_id(7);
	exit_button.title(font1,"Vissza",colors[0]);
	exit_button.title_pos(15,10);

	//Time screen
	Button time_button(90,540,55,55,"data/images/buttons/time1.png","data/images/buttons/time2.png");
	time_button.set_id(8);
	
	//Point screen
	Button point_screen(450,540,55,55,"data/images/buttons/point.png","data/images/buttons/point.png");
	point_screen.set_id(9);

	//Color's Buttons
	Button blue_button(0,0,165,110,"data/images/buttons/blue1.png","data/images/buttons/blue2.png");
	blue_button.set_id(2);
	Button green_button(0,0,165,110,"data/images/buttons/green1.png","data/images/buttons/green2.png");
	green_button.set_id(3);
	Button red_button(0,0,165,110,"data/images/buttons/red1.png","data/images/buttons/red2.png");
	red_button.set_id(4);
	Button yellow_button(0,0,165,110,"data/images/buttons/yellow1.png","data/images/buttons/yellow2.png");
	yellow_button.set_id(5);
	
	//Text Shown Button
	Button text_button(213,250,385,55,"data/images/buttons/textbutton.png","data/images/buttons/textbutton.png");
	text_button.set_id(9);
	text_button.set_title(false);
	
	//Set sound
	sound_load(&blue_button,&green_button,&red_button,&yellow_button,&exit_button,&time_button,sound);
	
	//Random positions
	offset1.x = 300;
	offset1.y = 257;
	offset2.x = 420;
	offset2.y = 257;
	mix_colors();
	drawn(font1,colors,&blue_button,&green_button,&red_button,&yellow_button,&text_button,color_pos,s_color,positions);
	search(text,color_text,&blue_button, &green_button, &red_button, &yellow_button, &t1_color, &t2_color);
	message1 = TTF_RenderUTF8_Blended(font3, text, colors[t1_color]);
	message2 = TTF_RenderUTF8_Blended(font3, color_text, colors[t2_color]);
	
	time_offset.y = 545;
	SDL_Surface *seconds = NULL;
	int temp_time=0;
	sprintf(s_points,"%d",points);
	Uint32 start = SDL_GetTicks();
	while(quit == false)
	{
		SDL_PollEvent(&event);
		if(event.type == SDL_QUIT)
		{
			exit_value = 1;
			quit = true;
		}
		if(event.type == SDL_KEYDOWN)
			if(event.key.keysym.sym == SDLK_ESCAPE)
				quit = true;	
				
		time_button.handle_events(event);
		time_button.show(screen);
		//Timer=======================
        std::stringstream time;
        if(temp_time == max_time + 1)
		{
			quit = true;
			break;
		}
        time << (temp_time = ((int)((SDL_GetTicks() - start)/1000))+1);
        seconds = TTF_RenderUTF8_Blended( font1, time.str().c_str(), colors[0] );
        if(temp_time < 10)
			time_offset.x =110;
		else
			time_offset.x =105;
        SDL_BlitSurface(seconds,NULL,screen,&time_offset);	
		//==============================
				
		exit_button.handle_events(event);
		exit_button.show(screen);
		name_button.show(screen);
		blue_button.handle_events(event);
		blue_button.show(screen);
		green_button.handle_events(event);
		green_button.show(screen);
		red_button.handle_events(event);
		red_button.show(screen);
		yellow_button.handle_events(event);
		yellow_button.show(screen);
		text_button.show(screen);
		point_screen.show(screen);
		
		point_surface = TTF_RenderUTF8_Blended( font2, s_points, colors[0] );
		SDL_BlitSurface(point_surface,NULL,screen,&t_offset);
		
		if(exit_button.get_push())
			break;
		SDL_BlitSurface(message1,NULL,screen,&offset1);
		SDL_BlitSurface(message2,NULL,screen,&offset2);
		SDL_Flip(screen);
		
		if(event.type == SDL_MOUSEBUTTONDOWN)
		{
			SDL_Delay(200);
			if(blue_button.get_push())
			{
				blue_button.set_push(false);
				if(good_button == blue_button.get_id())
				{
					push = true;
					start = SDL_GetTicks();
					points++;
				}
				else
					break;
			}
			if(green_button.get_push())
			{
				green_button.set_push(false);
				if(good_button == green_button.get_id())
				{
					push = true;
					start = SDL_GetTicks();
					points++;
				}
				else
					break;
			}
			if(red_button.get_push())
			{
				red_button.set_push(false);
				if(good_button == red_button.get_id())
				{
					push = true;
					start = SDL_GetTicks();
					points++;
				}
				else
					break;
			}
			if(yellow_button.get_push())
			{
				yellow_button.set_push(false);
				if(good_button == yellow_button.get_id())
				{
					push = true;
					start = SDL_GetTicks();
					points++;
				}
				else
					break;
			}
			sprintf(s_points,"%d",points);
		}
		if(push == true)
		{
			push = false;
			mix_colors();
			drawn(font1,colors,&blue_button,&green_button,&red_button,&yellow_button,&text_button,color_pos,s_color,positions);
			search(text,color_text,&blue_button, &green_button, &red_button, &yellow_button, &t1_color, &t2_color);
			message1 = TTF_RenderUTF8_Blended(font3, text, colors[t1_color]);
			message2 = TTF_RenderUTF8_Blended(font3, color_text, colors[t2_color]); 
		}
		
	}
	
	//Write data to file
	fprintf(out,"%s\t%d\t%d\n",player_name,points,max_time);
	
	fclose(out);
	TTF_CloseFont(font2);
	TTF_CloseFont(font3);
	TTF_CloseFont(font4);
	SDL_FreeSurface(backg);
	SDL_FreeSurface(name_surface);
	SDL_FreeSurface(message1);
	SDL_FreeSurface(message2);
	SDL_FreeSurface(seconds);
	SDL_FreeSurface(time_message);
	SDL_FreeSurface(point_message);
	SDL_FreeSurface(point_surface);
	return exit_value;
}

void settings(TTF_Font *font,TTF_Font *font2, SDL_Color *colors, int *time, char *player_name)
{
	
	Uint32 keyboard[36]={SDLK_a,SDLK_b,SDLK_c,SDLK_d,SDLK_e,SDLK_f,SDLK_g,SDLK_h,
		SDLK_i,SDLK_j,SDLK_k,SDLK_l,SDLK_m,SDLK_n,SDLK_o,SDLK_p,SDLK_q
		,SDLK_r,SDLK_s,SDLK_t,SDLK_u,SDLK_v,SDLK_w,SDLK_x,SDLK_y,SDLK_z,
		 SDLK_0,SDLK_1,SDLK_2,SDLK_3,SDLK_4,SDLK_5,SDLK_6,SDLK_7,SDLK_8,SDLK_9};

	SDL_Event event;
	SDL_Surface *setting_screen = NULL;
	SDL_Surface *message1 = NULL;
	SDL_Rect offset;
	SDL_Rect offset2;
	char name[30];
	char number[4];
	int count=0;
	int count2=0;
	bool in = false;
	bool in2 = false;
	offset.x = 225;
	offset.y = 40;
	offset2.x = 315;
	offset2.y = 10;
	
	setting_screen =  LoadWallpaper("data/images/backgrounds/setting.jpg");
	if(setting_screen == NULL)
		return;
	else
		SDL_BlitSurface(setting_screen,NULL,screen,&offset);
		
	//Name button
	Button name_in_button(300,90,220,55,"data/images/buttons/in_button.png","data/images/buttons/in_button.png");
	name_in_button.set_id(10);
	name_in_button.title_pos(0,8);
	
	//OK Button
	Button ok_button(325,500,165,55,"data/images/buttons/button1.png","data/images/buttons/button2.png");
	ok_button.over_sound_effect("data/sounds/button.wav");
	ok_button.push_sound_effect("data/sounds/button.wav");
	ok_button.set_id(11);
	ok_button.title(font,"Kész",colors[0]);
	ok_button.title_pos(50,7);
	
	//Set time button
	Button time_button(345,272,110,55,"data/images/buttons/setting_time.png","data/images/buttons/setting_time.png");
	time_button.set_id(12);
	
	message1 = TTF_RenderUTF8_Blended(font,"B e á l l í t á s o k", colors[4]);
	SDL_BlitSurface(message1,NULL,screen,&offset2);
	offset2.x = 370;
	offset2.y = 50;
	
	message1 = TTF_RenderUTF8_Blended(font,"N é v", colors[0]);
	SDL_BlitSurface(message1,NULL,screen,&offset2);
	
	message1 = TTF_RenderUTF8_Blended(font,"I d ő", colors[0]);
	offset2.y = 232;
	SDL_BlitSurface(message1,NULL,screen,&offset2);
	while(SDL_WaitEvent(&event))
	{
		if(event.type == SDL_QUIT)
			exit(1);
		
		name_in_button.handle_events(event);
		name_in_button.show(screen);
		ok_button.handle_events(event);
		ok_button.show(screen);
		time_button.handle_events(event);
		time_button.show(screen);
		
		if(name_in_button.get_push())
		{
			
			if(in == false)
			{
				in = true;
				if(count == 0)
				{
					name_in_button.title(font,"|",colors[0]);
				}
				else
				{
					name[count++] = '|';
					name[count] = '\0';
					name_in_button.title(font,name,colors[0]);
				}
				SDL_Flip(screen);
			}
			
			if(event.type == SDL_KEYDOWN)
			{
				Uint32 key;
				key = event.key.keysym.sym;
				
				if(key == SDLK_BACKSPACE)
				{
					if(count > 1)
					{
						name[--count] = '\0';
						name[count-1] = '|';
						name_in_button.title(font,name,colors[0]);
					}
				}
				
				if(key == SDLK_KP_ENTER)
				{
					name_in_button.set_push(false);
					name[--count] = '\0';
					name_in_button.title(font,name,colors[0]);
					in = false;
				}
				else
				{
					if(count < 14)
					{
						if(key == SDLK_SPACE)
						{
							if(count == 0)
							{
								name[count++] = ' ';
								name[count++] = '|';
							}
							else
							{
								name[count-1] = ' ';
								name[count++] = '|';
							}
							
							name[count] = '\0';
							name_in_button.title(font,name,colors[0]);
						}
						
						for(int i = 0; i < 36; i++)
						{
							if(key == keyboard[i])
							{
								if(count == 0)
								{
									name[count++] =  keyboard[i];
								}
								else
								{
									name[count-1] =  keyboard[i];
								}
								name[count++] = '|';
								name[count] = '\0';
								name_in_button.title(font,name,colors[0]);
							}
						}
					}
				}
			}
		}//Name Button
		
		//========================   Time Buton  ===========================================
		
		if(time_button.get_push())
		{
			
			if(in2 == false)
			{
				in2 = true;
				if(count2 == 0)
				{
					time_button.title(font,"|",colors[0]);
				}
				else
				{
					number[count2++] = '|';
					number[count2] = '\0';
					time_button.title(font,number,colors[0]);
				}
				SDL_Flip(screen);
			}
			
			if(event.type == SDL_KEYDOWN)
			{
				Uint32 key2;
				key2 = event.key.keysym.sym;
				
				if(key2 == SDLK_BACKSPACE)
				{
					if(count2 > 1)
					{
						number[--count2] = '\0';
						number[count2-1] = '|';
						time_button.title(font,number,colors[0]);
					}
				}
				
				if(key2 == SDLK_KP_ENTER)
				{
					time_button.set_push(false);
					number[--count2] = '\0';
					time_button.title(font,number,colors[0]);
					in2 = false;
				}
				else
				{
					if(count2 < 3)
					{
						if(key2 == SDLK_SPACE)
						{
							if(count2 == 0)
							{
								number[count2++] = ' ';
								number[count2++] = '|';
							}
							else
							{
								number[count2-1] = ' ';
								number[count2++] = '|';
							}
							
							number[count2] = '\0';
							time_button.title(font,number,colors[0]);
						}
						
						for(int i = 26; i < 36; i++)
						{
							if(key2 == keyboard[i])
							{
								if(count2 == 0)
								{
									number[count2++] =  keyboard[i];
								}
								else
								{
									number[count2-1] =  keyboard[i];
								}
								number[count2++] = '|';
								number[count2] = '\0';
								time_button.title(font,number,colors[0]);
							}
						}
					}
				}
			}
		}
		
		//===========================================================================================
		
		if(event.type == SDL_MOUSEBUTTONDOWN && in == true)
		{
			if(!name_in_button.get_over())
			{
				name_in_button.set_push(false);
				name[--count] = '\0';
				name_in_button.title(font,name,colors[0]);
				in = false;
			}
		}
		if(event.type == SDL_MOUSEBUTTONDOWN && in2 == true)
		{
			if(!time_button.get_over())
			{
				time_button.set_push(false);
				number[--count2] = '\0';
				time_button.title(font,number,colors[0]);
				in2 = false;
			}
		}
		
		if(ok_button.get_push())
		{
			if(count > 0 && count2 > 0)
				break;
		}
		SDL_Flip(screen);
	}
	strcpy(player_name,name);
	int num1,num2;
	num1 = number[0] - '0';
	if(count2 == 1)
	{
		num2 = 0;
		*time = num1;
	}
	else
	{
		num2 = number[1] - '0';
		*time = (num1 * 10) + num2;
	}
	
	SDL_FreeSurface(message1);
	SDL_FreeSurface(setting_screen);
	return;
}

void mix_colors()
{
	place_blue = place_green = place_red = place_yellow = 0;
	cplace_blue = cplace_green = cplace_red = cplace_yellow = 0;
	
	//Blue
	place_blue = rand() % 4;
	cplace_blue = rand() % 4;
	
	//Green
	do
	{
		place_green = rand() % 4;
		cplace_green = rand() % 4;
		
	}while((place_blue == place_green) || (cplace_blue == cplace_green));
	
	//Red
	do
	{
		place_red = rand() % 4;
		cplace_red = rand() % 4;
		
	}while((place_blue == place_red) || (place_green == place_red) || (cplace_blue == cplace_red) || (cplace_green == cplace_red));
	
	//Yellow Button
	do
	{
		place_yellow = rand() % 4;
		cplace_yellow = rand() % 4;
			
	}while((place_blue == place_yellow) || (place_green == place_yellow) || (place_red == place_yellow) || 
		(cplace_blue == cplace_yellow) || (cplace_green == cplace_yellow) || (cplace_red == cplace_yellow));
	
	return;
}

void drawn(TTF_Font *font1, SDL_Color *textcolor, Button *blue_button, Button *green_button, Button *red_button, Button *yellow_button,
			Button *text_button, const int *color_pos, const char *s_color[], const int *positions)
{
	blue_button->change_pos(positions[place_blue],100);
	blue_button->title(font1,s_color[cplace_blue],textcolor[1]);
	blue_button->title_pos(color_pos[cplace_blue],31);
	
	green_button->change_pos(positions[place_green],100);
	green_button->title(font1,s_color[cplace_green],textcolor[1]);
	green_button->title_pos(color_pos[cplace_green],31);
	
	red_button->change_pos(positions[place_red],100);
	red_button->title(font1,s_color[cplace_red],textcolor[1]);
	red_button->title_pos(color_pos[cplace_red],31);
	
	yellow_button->change_pos(positions[place_yellow],100);
	yellow_button->title(font1,s_color[cplace_yellow],textcolor[1]);
	yellow_button->title_pos(color_pos[cplace_yellow],31);
	
	return;
}

void sound_load(Button *one, Button *two, Button *three,Button *four, Button *five, Button *six, bool sound)
{	
	
	//one -> over_sound_effect("data/sounds/button.wav");
	//one -> push_sound_effect("data/sounds/button.wav");
	//two -> over_sound_effect("data/sounds/button.wav");
	//two -> push_sound_effect("data/sounds/button.wav");
	//three -> over_sound_effect("data/sounds/button.wav");
	//three -> push_sound_effect("data/sounds/button.wav");
	//four -> over_sound_effect("data/sounds/button.wav");
	//four -> push_sound_effect("data/sounds/button.wav");
	five -> over_sound_effect("data/sounds/button.wav");
	//five -> push_sound_effect("data/sounds/button.wav");
	six -> over_sound_effect("data/sounds/button.wav");
	//six -> push_sound_effect("data/sounds/button.wav");
	
	if(sound == true)
	{
		//one -> set_push_sound(true);
		//two -> set_push_sound(true);
		//three -> set_push_sound(true);
		//four -> set_push_sound(true);
		//five -> set_push_sound(true);
		//six -> set_push_sound(true);
		/*one -> set_over_sound(true);
		two -> set_over_sound(true);
		three -> set_over_sound(true);
		four -> set_over_sound(true);*/
		five -> set_over_sound(true);
		six -> set_over_sound(true);
	}
	else if(sound == false)
	{
		/*one -> set_push_sound(false);
		two -> set_push_sound(false);
		three -> set_push_sound(false);
		four -> set_push_sound(false);
		five -> set_push_sound(false);
		six -> set_push_sound(false);
		one -> set_over_sound(false);
		two -> set_over_sound(false);
		three -> set_over_sound(false);
		four -> set_over_sound(false);*/
		five -> set_over_sound(false);
		six -> set_over_sound(false);
	}
}

void search(char *text, char *color, Button *blue, Button *green, Button *red, Button *yellow, int *t1_color, int *t2_color)
{
	bool szoveg;
	char search[15];
	
	if(rand()%2 == 0)
	{
		szoveg = true;
		sprintf(text,"Szöveg  : ");
		good_button = rand() % 4 + 2;
		
		if((blue -> get_id()) == good_button)
		{
			blue -> get_title(search);
			strcpy(color,search);
		}
		
		if(green -> get_id() == good_button)
		{
			green -> get_title(search);
			strcpy(color,search);
		}
		
		if(red -> get_id() == good_button)
		{
			red -> get_title(search);
			strcpy(color,search);
		}
		
		if(yellow -> get_id() == good_button)
		{
			yellow -> get_title(search);
			strcpy(color,search);
		}
		
	}
	else
	{	szoveg = false;
		sprintf(text,"Szín        :");
		good_button = rand() % 4 + 2;
		switch(good_button-2)
		{
			case 0 : sprintf(color,"Kék");break;
			case 1 : sprintf(color,"Zöld");break;
			case 2 : sprintf(color,"Piros");break;
			case 3 : sprintf(color,"Sárga");break;
		}
	}
		
	
	if(szoveg == true)
	{
		blue -> get_title(search);
		if((strcmp(search,color)) == 0)
			good_button = blue -> get_id();
				
		green -> get_title(search);
		if((strcmp(search,color)) == 0)
			good_button = green -> get_id();
				
		red -> get_title(search);
		if((strcmp(search,color)) == 0)
			good_button = red -> get_id();
				
		yellow -> get_title(search);
		if((strcmp(search,color)) == 0)
			good_button = yellow -> get_id();
	}
	
	printf("good_button = %d\n",good_button);
	switch(good_button)
	{
		case 2 : printf("Kék gomb\n");break;
		case 3 : printf("Zöld gomb\n");break;
		case 4 : printf("Piros gomb\n");break;
		case 5 : printf("Sárga gomb\n");break;
	}
	
	do
	{
		*t1_color = rand() % 4 + 2;
		
	}while(*t1_color == good_button);
	*t2_color = rand() % 4 + 2;
	
	return;
}

SDL_Surface* LoadWallpaper(const char *titles)
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
	return optimizedImage;
    
}
