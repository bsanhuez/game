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
void fondo();
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
BITMAP *pj;
BITMAP *chr;
PALETTE paleta;

float player_x = 400;
float player_y = 300;
int dir = 3;

void main(){
	
	int enciclopedia[19][2];
	
	
	caotyks_inicio();
	
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
	pj = load_bitmap("media/jym.bmp",NULL);
	bmp = load_bitmap("media/fondo.bmp",NULL);
	
	
	blit(pj,chr,0,0,0,0,32,42);	
	draw_sprite(bmp,chr,player_x,player_y);
	blit(bmp,screen,0,0,0,0,800,600);	
}

void caotyks_inicio(){
	
	caos[0] = {'Botyk','vacuna','fuego',10,10,1000}, 
	//etapa 0
	caos[1] = {'Bokoryk','vacuna','fuego',50,30,3000},
	caos[2] = {'Botsukoyk','data','agua',30,50,3000},
	//etapa 1
	caos[3] = {'Taytyk','virus','fuego',100,50,10000},
	caos[4] = {'Dinotyk','vacuna','fuego',100,100,5000},
	caos[5] = {'Flamyk','data','fuego',80,100,7000},
	caos[6] = {'Armadyk','vacuna','hierba',100,150,10000},
	caos[7] = {'Wolfyk','data','agua',100,100,7000},
	caos[8] = {'Floryk','vacuna','hierba',150,100,5000},
	//etapa 2
	caos[9] = {'MetalDinotyk','virus','acero',300,300,10000},
	caos[10] = {'Lagutyk','data','agua',500,100,7000},
	caos[11]= {'Weretyk','virus','trueno',200,300,10000},
	caos[12]= {'Togyk','virus','madera',500,300,10000},
	//etapa 3
	caos[13]= {'Duketyk','data','acero',2000,600,20000},
	caos[14]= {'Omegatyk','vacuna','trueno',3000,1000,15000},
	caos[15]= {'SatanDinotyk','virus','fuego',4000,500,13000},
	caos[16]= {'Chaostyk','virus','acero',2000,500,11000},
	caos[17]= {'Valktyk','vacuna','hierba',3000,1000,20000},
	caos[18]= {'BlackOmegatyk','virus','trueno',1000,3000,15000},
	caos[19]= {'Zerotyk','vacuna','madera',5000,1000,10000};
	
}
