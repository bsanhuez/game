#include<allegro.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<unistd.h>
void inicio();
void fondo();
void movimiento();
void _menu();
void fondo();
void batalla();

BITMAP *menu;
BITMAP *bmp;
BITMAP *pj;
BITMAP *chr;
PALETTE paleta;

float player_x = 400;
float player_y = 300;
int dir = 3;

void main(){
	
	
	allegro_init();
	inicio();
	
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0);	
	
	_menu();
	fondo();
	
	
	
	while(!key[KEY_ESC]){
			
		movimiento();
			
	}
	
	
	destroy_bitmap(bmp);
	destroy_bitmap(chr);
	destroy_bitmap(pj);
	allegro_exit();
		
}
END_OF_MAIN();

void inicio(){
	
	get_palette(paleta);
	install_keyboard();
	install_mouse();
	install_timer();
	
}

void movimiento(){
	
			if(key[KEY_LEFT]){	
			
				bmp = load_bitmap("media/fondo.bmp",NULL);	
				draw_sprite(bmp,chr,player_x,player_y);
				player_x = player_x - 1.5;
				blit(bmp,screen,0,0,0,0,800,600);
				
			}
			
			if(key[KEY_RIGHT]){	
				
				
				bmp = load_bitmap("media/fondo.bmp",NULL);
				draw_sprite(bmp,chr,player_x,player_y);
				player_x = player_x + 1.5;
				blit(bmp,screen,0,0,0,0,800,600);
			
			
			}
			
			if(key[KEY_UP]){	
			
				
				bmp = load_bitmap("media/fondo.bmp",NULL);
				
				draw_sprite(bmp,chr,player_x,player_y);
				player_y = player_y - 1.5;
				blit(bmp,screen,0,0,0,0,800,600);
			
			}
			
			if(key[KEY_DOWN]){	
			
				bmp = load_bitmap("media/fondo.bmp",NULL);
				
				draw_sprite(bmp,chr,player_x,player_y);
				player_y = player_y + 1.5;
				blit(bmp,screen,0,0,0,0,800,600);
				
			}	
	
	
}

void _menu(){
	
	menu = load_bitmap("media/mmenu.bmp",NULL);
	
	
	do{
		
		blit(menu,screen,0,0,0,0,800,600);
		
		if(key[KEY_ESC]){
			
			allegro_exit();
		}
		
	}while(!key[KEY_ENTER]);
	
	destroy_bitmap(menu);
}

void fondo(){
	
	bmp = create_bitmap(800, 600); 
	chr = create_bitmap(32,42);
	pj = load_bitmap("media/jym.bmp",NULL);
	bmp = load_bitmap("media/fondo.bmp",NULL);
	
	
	blit(pj,chr,0,0,0,0,32,42);	
	draw_sprite(bmp,chr,player_x,player_y);
	blit(bmp,screen,0,0,0,0,800,600);	
}
