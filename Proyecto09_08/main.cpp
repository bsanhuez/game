#include<allegro.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<unistd.h>

void inicio();
void caotyks_inicio();
void fondo();
void movimiento();
void _menu();
void batalla();

struct caotyks{
	
	char nombre[20]; //Nombre del Monstruo
	char tipo[10]; //atributo principal "vacuna,data,virus"
	char tipo_b[10]; //atributo secundario "fuego,agua,hierba" o "madera,trueno,acero
	int atk; //ataque base
	int def; // defensa base
	int vida; // vida base
	
}caos[19];

BITMAP *menu;
BITMAP *bmp;
BITMAP *pjaba;
BITMAP *pjarr;	
BITMAP *pjder;
BITMAP *pjizq;
BITMAP *chr;
PALETTE paleta;

float player_x = 400;
float player_y = 300;
int dir = 3;
int conteo = 0;
int numconteo = 0;
int aux_conteo = 0;

void main(){
	
	int enciclopedia[19][2];
	
	srand(time(NULL));
	
	caotyks_inicio();
	
	allegro_init();
	inicio();	
	
	_menu();
	fondo();
	
	
	
	while(!key[KEY_ESC]){
			
		movimiento();
			
	}
	
	
	
	destroy_bitmap(chr);
	destroy_bitmap(pjaba);
	allegro_exit();
		
}
END_OF_MAIN();

void inicio(){
	
	get_palette(paleta);
	install_keyboard();
	install_mouse();
	install_timer();
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0);
	
}

void movimiento(){
		
			if(aux_conteo == 0){
		
				numconteo = 1 + rand() % ((200+1)-1);
				aux_conteo = 1;
					
			}
			
		destroy_bitmap(bmp);
		bmp = load_bitmap("media/fondo.bmp",NULL);
		

		
			if(key[KEY_LEFT] && !key[KEY_UP] && !key[KEY_DOWN] && !key[KEY_RIGHT]){	
				
				
				blit(pjizq,chr,0,0,0,0,32,42);	
				draw_sprite(bmp,chr,player_x,player_y);
				player_x = player_x - 1;
				
				if(key[KEY_X]){
					
					player_x = player_x - 3;
		
				}
				
				conteo ++;
				
				batalla();
				
				
				blit(bmp,screen,0,0,0,0,800,600);
				
				
			}
			
			if(key[KEY_RIGHT] && !key[KEY_UP] && !key[KEY_DOWN] && !key[KEY_LEFT]){	
				
				
				blit(pjder,chr,0,0,0,0,32,42);
				draw_sprite(bmp,chr,player_x,player_y);
				player_x = player_x + 1;
				
				if(key[KEY_X]){
					
					player_x = player_x + 3;
					
				}
				
				conteo ++;
				
				batalla();
				
				blit(bmp,screen,0,0,0,0,800,600);
				
			
			}
			
			if(key[KEY_UP] && !key[KEY_LEFT] && !key[KEY_DOWN] && !key[KEY_RIGHT]){	
			
				
				blit(pjarr,chr,0,0,0,0,32,42);
				draw_sprite(bmp,chr,player_x,player_y);
				player_y = player_y - 1;
				
				if(key[KEY_X]){
					
					player_y = player_y - 3;
					
				}
				
				conteo ++;
				
				batalla();
				
				blit(bmp,screen,0,0,0,0,800,600);
				
			
			}
			
			if(key[KEY_DOWN] && !key[KEY_UP] && !key[KEY_LEFT] && !key[KEY_RIGHT]){	
				
				
				blit(pjaba,chr,0,0,0,0,32,42);
				draw_sprite(bmp,chr,player_x,player_y);
				player_y = player_y + 1;
				
				if(key[KEY_X]){
					
					player_y = player_y + 3;
					
				}
				
				conteo ++;
				
				batalla();
				
				blit(bmp,screen,0,0,0,0,800,600);
				
				
			}	
	
	
}

void _menu(){
	
	menu = load_bitmap("media/menu.bmp",NULL);
	
	
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
	pjaba = load_bitmap("media/JymAba.bmp",NULL);
	pjarr = load_bitmap("media/JymArr.bmp",NULL);
	pjizq = load_bitmap("media/JymIzq.bmp",NULL);
	pjder = load_bitmap("media/JymDer.bmp",NULL);
	bmp = load_bitmap("media/fondo.bmp",NULL);
	
	
	blit(pjaba,chr,0,0,0,0,32,42);	
	draw_sprite(bmp,chr,player_x,player_y);
	blit(bmp,screen,0,0,0,0,800,600);	
}

void caotyks_inicio(){

	
	
}

void batalla(){

	
	if(conteo == numconteo){
		
		_menu();
		conteo = 0;
		aux_conteo = 0;
	}
	
}
