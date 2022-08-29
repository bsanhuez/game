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
void batalla_carga();
void loadspr(int caos_jugador,int caos_enemigo);
void mostrar_caos(int caos_jugador,int caos_enemigo);
void evolucion(int enemigo_conteo[20]);
void registro();

struct caotyks{
	
	char nombre[20]; //Nombre del Monstruo
	char tipo[10]; //atributo principal "vacuna,data,virus"
	char tipo_b[10]; //atributo secundario "fuego,agua,hierba" o "madera,trueno,acero
	int atk; //ataque base
	int def; // defensa base
	int vida; // vida base
	
}caos[20]; // ARREGLAR

BITMAP *menu;
BITMAP *bmp;
BITMAP *pjaba;
BITMAP *pjarr;
BITMAP *pjder;
BITMAP *pjizq;
BITMAP *chr;
BITMAP *batalla_fondo;
BITMAP *caos_play;
BITMAP *caos_playnt;
BITMAP *caos_a;
BITMAP *caos_b;
BITMAP *reg;

//769X, 559Y Limite inferior derecho, Limite inferior abajo
//1X, 1Y Limite superior izquierdo, Limite superior arriba

int player_x = 300;
int player_y = 200;
int mapa = 0;
int conteo = 0;
int numconteo = 0;
int aux_conteo = 0;
int in_battle = 0;
int caos_jugador = 0;
int victoria = 0;
int derrota = 0;
int enciclopedia[20];
int puntaje = 0;

void main(){
	
	int i = 0;
	
	srand(time(NULL));
	
	caotyks_inicio();
	allegro_init();
	inicio();	
	
	_menu();
	fondo();
	
	for(i=0;i<20;i++){
		
		enciclopedia[i] = 0;
		
	}
	
	
	
	while(!key[KEY_ESC]){
		
		
		movimiento();
		
		
	}
			
	
	
	destroy_bitmap(menu);
	destroy_bitmap(bmp);
	destroy_bitmap(batalla_fondo);
	destroy_bitmap(chr);
	destroy_bitmap(pjaba);
	destroy_bitmap(pjder);
	destroy_bitmap(pjarr);
	destroy_bitmap(pjizq);
	allegro_exit();
		
}
END_OF_MAIN();

void inicio(){
	
	install_keyboard();
	install_mouse();
	install_timer();
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0);
	
}

void movimiento(){
			

			textprintf_ex(screen, font, 50,50, makecol(0, 0, 0),-1, "VICTORIAS : %d",victoria);
			textprintf_ex(screen, font, 50,70, makecol(0, 0, 0),-1, "DERROTAS : %d",derrota);
			
			
			//420 tope puerta abajo y 320 tope puerta abajo arriba
			//370 arriba iqz y 470
			
			if(aux_conteo == 0){
		
				numconteo = 1 + rand() % ((250+1)-1);
				aux_conteo = 1;
					
			}
			
				destroy_bitmap(bmp);
				
				if(key[KEY_Q]){
					
					mapa = 0;//pradera 1
				}else if(key[KEY_W] && victoria >21){
					
					mapa = 1;//pradera 2
				}else if(key[KEY_E] && victoria >61){
					
					mapa = 2;//circuito
				}else if(key[KEY_R] && victoria >61){
					
					mapa = 3;//cueva
				}
				
				switch(mapa){
					
					case 0 : 
							bmp = load_bitmap("media/fondo.bmp",NULL);					
					;break;
					case 1 : 
							bmp = load_bitmap("media/fondo2.bmp",NULL);
					;break;
					case 2 : 
							bmp = load_bitmap("media/fondo3.bmp",NULL);
					;break;
					case 3 : 
							bmp = load_bitmap("media/fondo4.bmp",NULL);
					;break;
					
					default : 
							bmp = load_bitmap("media/fondo.bmp",NULL);
					;break;
					
				}



			
			
		
			if(key[KEY_LEFT] && !key[KEY_UP] && !key[KEY_DOWN] && !key[KEY_RIGHT] && player_x > 15){	
			
				blit(pjizq,chr,0,0,0,0,32,42);	
				draw_sprite(bmp,chr,player_x,player_y);			
				player_x = player_x - 1;
				
				if(key[KEY_X]){
					
					player_x = player_x - 2;
		
				}
				
				
				conteo ++;
				
				batalla();
				
				blit(bmp,screen,0,0,0,0,800,600);
				
				

			
			}
			
			if(key[KEY_RIGHT] && !key[KEY_UP] && !key[KEY_DOWN] && !key[KEY_LEFT] && player_x < 750){	
				
				
				blit(pjder,chr,0,0,0,0,32,42);
				draw_sprite(bmp,chr,player_x,player_y);
				player_x = player_x + 1;
				
				if(key[KEY_X]){
					
					player_x = player_x + 2;
					
				}
				
				conteo ++;
				
				batalla();
				
				blit(bmp,screen,0,0,0,0,800,600);
				
			
			}
			
			if(key[KEY_UP] && !key[KEY_LEFT] && !key[KEY_DOWN] && !key[KEY_RIGHT] && player_y > 15){	
			
				
				blit(pjarr,chr,0,0,0,0,32,42);
				draw_sprite(bmp,chr,player_x,player_y);
				
				player_y = player_y - 1;
				if(key[KEY_X]){
					
					player_y = player_y - 2;
					
				}
				
				conteo ++;
				
				batalla();
				
				blit(bmp,screen,0,0,0,0,800,600);
				
			
			}
			
			if(key[KEY_DOWN] && !key[KEY_UP] && !key[KEY_LEFT] && !key[KEY_RIGHT] && player_y < 540){	
				
				
				blit(pjaba,chr,0,0,0,0,32,42);
				draw_sprite(bmp,chr,player_x,player_y);
				player_y = player_y + 1;
				
				if(key[KEY_X]){
					
					player_y = player_y + 2;
					
				}
				
				conteo ++;
				
				batalla();
				
				blit(bmp,screen,0,0,0,0,800,600);
				
				
			}	
			
			
			
		if(key[KEY_A]){
			
			registro();
			
		}
		
		draw_sprite(bmp,chr,player_x,player_y);
		blit(bmp,screen,0,0,0,0,800,600);
		
		
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
		
	blit(pjaba,chr,0,0,0,0,32,42);	
	draw_sprite(bmp,chr,player_x,player_y);
	
	
}

void caotyks_inicio(){

	int i = 0;
	FILE *enemigos;
	enemigos = fopen("caotyks.txt","rt");
	
	for(i=0;i<20;i++){
		
		fscanf(enemigos,"%s ",caos[i].nombre);
		fscanf(enemigos,"%s ",caos[i].tipo);
		fscanf(enemigos,"%s ",caos[i].tipo_b);
		fscanf(enemigos,"%d ",&caos[i].atk);
		fscanf(enemigos,"%d ",&caos[i].def);
		fscanf(enemigos,"%d",&caos[i].vida);
		
	}
	fclose (enemigos);
	
}

void batalla(){

	
	int pociones = 3;
	
	if(conteo == numconteo){
		
		batalla_carga();
		conteo = 0;
		aux_conteo = 0;
	}
	
}

 void batalla_carga(){
	
	int opcion[2];
	
	opcion[0] = 0;//pocion - inactivo "0"
	opcion[1] = 1;//atacar - activo "1"
	opcion[2] = 0;//escapar - inactivo "0"
	
	int caos_enemigo = 0;
	int damage_player = 0;
	int damage_enemy = 0;
	int aux_vida = 0;
	int aux_vida_e = 0;
	int pocion = 3;
	int enemigo_conteo[20];
	int i = 0;
	
	for(i=0;i<20;i++){
		
		enemigo_conteo[i] = 0;
		
	}
	
	in_battle = 1;
	
	if(caos_jugador == 0 && mapa == 0 || mapa == 1){ //bebe y entrenamiento
		caos_enemigo = 0 + rand() % ((3+1)-1);
		
	}else if(caos_jugador <= 6 && mapa == 0 || mapa == 1){ // bebe, entrenamiento y adulto
		caos_enemigo = 1 + rand() % ((8+1)-1);
		
	}else if(caos_jugador <=13 && mapa == 2 || mapa == 3){ // bebe, entrenamiento y adulto
		caos_enemigo = 1 + rand() % ((12+1)-1);
	
	}else if(caos_jugador <=20 && mapa == 3){ // bebe, entrenamiento, adulto y mega
		caos_enemigo = 1 + rand() % ((18+1)-1);
		if(caos_enemigo > 20){
			caos_enemigo = 19;
		}
	}
	
	
	aux_vida = caos[caos_jugador].vida;
	aux_vida_e = caos[caos_enemigo].vida;
	
	
	destroy_bitmap(batalla_fondo);
	
	if(mapa == 0){
		
	batalla_fondo = load_bitmap("media/batalla1.bmp",NULL);		
		
	}else if(mapa == 1){
		
	batalla_fondo = load_bitmap("media/batalla1.bmp",NULL);	
		
	}else if(mapa == 2){
		
	batalla_fondo = load_bitmap("media/batallacircuito1.bmp",NULL);	
		
	}else if(mapa == 3){
		
	batalla_fondo = load_bitmap("media/batallacueva1.bmp",NULL);	
		
	}
	

	
	loadspr(caos_jugador,caos_enemigo);
	mostrar_caos(caos_jugador,caos_enemigo);
		
		
	do{

		blit(batalla_fondo,screen,0,0,0,0,800,600);
		
		if(opcion[0] == 0 && opcion[1] == 1 && opcion[2] == 0){//atacar
				
		destroy_bitmap(batalla_fondo);
		
			if(mapa == 0){
		
			batalla_fondo = load_bitmap("media/batalla1.bmp",NULL);		
		
			}else if(mapa == 1){
		
			batalla_fondo = load_bitmap("media/batalla1.bmp",NULL);	
		
			}else if(mapa == 2){
		
			batalla_fondo = load_bitmap("media/batallacircuito1.bmp",NULL);	
		
			}else if(mapa == 3){
		
			batalla_fondo = load_bitmap("media/batallacueva1.bmp",NULL);	
		
			}
		
		textprintf_ex(batalla_fondo, font, 50, 210, makecol(0, 0, 0),-1, "%d / %d", aux_vida,caos[caos_jugador].vida);
		textprintf_ex(batalla_fondo, font, 650, 210, makecol(0, 0, 0),-1, "%d / %d", aux_vida_e,caos[caos_enemigo].vida);
		textprintf_ex(batalla_fondo, font, 75, 190, makecol(0, 0, 0),-1, "%s",caos[caos_jugador].nombre);
		textprintf_ex(batalla_fondo, font, 670, 190, makecol(0, 0, 0),-1, "%s",caos[caos_enemigo].nombre);
		textprintf_ex(batalla_fondo, font, 210, 55, makecol(0, 0, 0),-1, "X %d", pocion);
		
		mostrar_caos(caos_jugador,caos_enemigo);
		
		blit(batalla_fondo,screen,0,0,0,0,800,600);	
	
			
			
			if(key[KEY_Z]){
					
					
					if(caos[caos_jugador].tipo == caos[caos_enemigo].tipo || caos[caos_jugador].tipo_b == caos[caos_enemigo].tipo_b ){//1 tipo igual
						
						damage_player = (caos[caos_jugador].atk * 1.2) - caos[caos_enemigo].def;
						aux_vida_e = aux_vida_e - damage_player;
						
						damage_enemy = (caos[caos_enemigo].atk * 1.2) - caos[caos_jugador].def;
						aux_vida = aux_vida - damage_enemy;
						
						damage_player = 0;
						damage_enemy = 0;
							
					}
					
					
					if(caos[caos_jugador].tipo == caos[caos_enemigo].tipo && caos[caos_jugador].tipo_b == caos[caos_enemigo].tipo_b){//los dos tipos iguales
						
						damage_player = caos[caos_jugador].atk - (caos[caos_enemigo].def / 2);
						aux_vida_e = aux_vida_e - damage_player;
						
						damage_enemy = caos[caos_enemigo].atk - (caos[caos_jugador].def / 2);
						aux_vida = aux_vida - damage_enemy;
						
						damage_player = 0;
						damage_enemy = 0;
						
					}
					
					if(caos[caos_jugador].tipo != caos[caos_enemigo].tipo && caos[caos_jugador].tipo_b != caos[caos_enemigo].tipo_b){// dos tipos diferentes
						
						damage_player = caos[caos_jugador].atk - caos[caos_enemigo].def;
						aux_vida_e = aux_vida_e - damage_player;
						
						damage_enemy = caos[caos_enemigo].atk - caos[caos_jugador].def;
						aux_vida = aux_vida - damage_enemy;
						
						damage_player = 0;
						damage_enemy = 0;
						
					}
				
				
				if(aux_vida_e <= 0 || aux_vida <= 0){
					
					if(aux_vida_e <= 0){
						
						victoria++;
						
						enemigo_conteo[caos_enemigo] ++;
						
					}else if(aux_vida <= 0){
						
						derrota++;
						
					}
					
					in_battle = 0;
					aux_vida = 0;
					aux_vida_e = 0;
					
				}
				
			}
			
			if(key[KEY_LEFT]){
				
				opcion[1] = 0;
				opcion[0] = 1;
				
			}else if(key[KEY_RIGHT]){
				
				opcion[1] = 0;
				opcion[2] = 1;
				
			}
			
		}
		
		
		
		
		
		
		if(opcion[0] == 1 && opcion[1] == 0 && opcion[2] == 0){//Pocion


		
		destroy_bitmap(batalla_fondo);
		
		if(mapa == 0){
		
			batalla_fondo = load_bitmap("media/batalla0.bmp",NULL);		
		
			}else if(mapa == 1){
		
			batalla_fondo = load_bitmap("media/batalla0.bmp",NULL);	
		
			}else if(mapa == 2){
		
			batalla_fondo = load_bitmap("media/batallacircuito0.bmp",NULL);	
		
			}else if(mapa == 3){
		
			batalla_fondo = load_bitmap("media/batallacueva0.bmp",NULL);	
		
			}
			
		textprintf_ex(batalla_fondo, font, 50, 210, makecol(0, 0, 0),-1, "%d / %d", aux_vida,caos[caos_jugador].vida);
		textprintf_ex(batalla_fondo, font, 650, 210, makecol(0, 0, 0),-1, "%d / %d", aux_vida_e,caos[caos_enemigo].vida);
		textprintf_ex(batalla_fondo, font, 75, 190, makecol(0, 0, 0),-1, "%s",caos[caos_jugador].nombre);
		textprintf_ex(batalla_fondo, font, 670, 190, makecol(0, 0, 0),-1, "%s",caos[caos_enemigo].nombre);
		textprintf_ex(batalla_fondo, font, 210, 55, makecol(0, 0, 0),-1, "X %d", pocion);
		
		mostrar_caos(caos_jugador,caos_enemigo);
		
		blit(batalla_fondo,screen,0,0,0,0,800,600);
					
			if(key[KEY_Z]){
				
				
				
				while (aux_vida < caos[caos_jugador].vida && pocion != 0){
					aux_vida = aux_vida + 1000;
					
					if(aux_vida > caos[caos_jugador].vida){
						
						aux_vida = caos[caos_jugador].vida; 
						
					}
					
					pocion--;
					
				}
				
			}
					
					
			if(key[KEY_RIGHT]){
				
				opcion[0] = 0;
				opcion[2] = 1;
		
			}else if(key[KEY_DOWN]){
				
				opcion[0] = 0;
				opcion[1] = 1;
				opcion[2] = 0;
			}
			
		}
		
		
		
				
		
		if(opcion[0] == 0 && opcion[1] == 0 && opcion[2] == 1){//escapar
		
		destroy_bitmap(batalla_fondo);
		
		if(mapa == 0){
		
			batalla_fondo = load_bitmap("media/batalla2.bmp",NULL);		
		
			}else if(mapa == 1){
		
			batalla_fondo = load_bitmap("media/batalla2.bmp",NULL);	
		
			}else if(mapa == 2){
		
			batalla_fondo = load_bitmap("media/batallacircuito2.bmp",NULL);	
		
			}else if(mapa == 3){
		
			batalla_fondo = load_bitmap("media/batallacueva2.bmp",NULL);	
		
			}
			
		textprintf_ex(batalla_fondo, font, 50, 210, makecol(0, 0, 0),-1, "%d / %d", aux_vida,caos[caos_jugador].vida);
		textprintf_ex(batalla_fondo, font, 650, 210, makecol(0, 0, 0),-1, "%d / %d", aux_vida_e,caos[caos_enemigo].vida);
		textprintf_ex(batalla_fondo, font, 75, 190, makecol(0, 0, 0),-1, "%s",caos[caos_jugador].nombre);
		textprintf_ex(batalla_fondo, font, 670, 190, makecol(0, 0, 0),-1, "%s",caos[caos_enemigo].nombre);
		textprintf_ex(batalla_fondo, font, 210, 55, makecol(0, 0, 0),-1, "X %d", pocion);
		
		mostrar_caos(caos_jugador,caos_enemigo);
		
		blit(batalla_fondo,screen,0,0,0,0,800,600);
							
			if(key[KEY_Z]){
				
				in_battle = 0;
				aux_vida = 0;
				aux_vida_e = 0;
				
			}else if(key[KEY_LEFT]){
				
				opcion[0] = 1;
				opcion[2] = 0;
				
			}else if(key[KEY_DOWN]){
				
				opcion[0] = 0;
				opcion[1] = 1;
				opcion[2] = 0;
			}
			
		}

		
		
	}while(in_battle == 1);
	
	evolucion(enemigo_conteo);
	
	
}

void loadspr(int caos_jugador,int caos_enemigo){


	switch(caos_jugador){
		
		case 0 : 
					caos_play = load_bitmap("media/caos_sprites/0.bmp",NULL);
		
		;break;
		
		case 1 :
					caos_play = load_bitmap("media/caos_sprites/1.bmp",NULL);
		
		 ;break;
		
		case 2 : 
					caos_play = load_bitmap("media/caos_sprites/2.bmp",NULL);
		
		;break;
		
		case 3 : 
					caos_play = load_bitmap("media/caos_sprites/3.bmp",NULL);
		
		;break;
		
		case 4 : 
					caos_play = load_bitmap("media/caos_sprites/4.bmp",NULL);
		
		;break;
		
		case 5 : 
					caos_play = load_bitmap("media/caos_sprites/5.bmp",NULL);

		;break;
		
		case 6 : 
					caos_play = load_bitmap("media/caos_sprites/6.bmp",NULL);
		
		;break;
		
		case 7 : 
					caos_play = load_bitmap("media/caos_sprites/7.bmp",NULL);
		
		;break;
		
		case 8 :
					caos_play = load_bitmap("media/caos_sprites/8.bmp",NULL);
		
		 ;break;
		
		case 9 : 
					caos_play = load_bitmap("media/caos_sprites/9.bmp",NULL);
		
		;break;
		
		case 10 : 
					caos_play = load_bitmap("media/caos_sprites/10.bmp",NULL);
		
		;break;
		
		case 11 : 
					caos_play = load_bitmap("media/caos_sprites/11.bmp",NULL);
		
		;break;
		
		case 12 : 
					caos_play = load_bitmap("media/caos_sprites/12.bmp",NULL);

		;break;
		
		case 13 : 
					caos_play = load_bitmap("media/caos_sprites/13.bmp",NULL);
		
		;break;
		
		case 14 : 
					caos_play = load_bitmap("media/caos_sprites/14.bmp",NULL);
		
		;break;
		
		case 15 :
					caos_play = load_bitmap("media/caos_sprites/15.bmp",NULL);
		
		 ;break;
		
		case 16 : 
					caos_play = load_bitmap("media/caos_sprites/16.bmp",NULL);
		
		;break;
		
		case 17 : 
					caos_play = load_bitmap("media/caos_sprites/17.bmp",NULL);
		
		;break;
		
		case 18 : 
					caos_play = load_bitmap("media/caos_sprites/18.bmp",NULL);
		
		;break;
		
		case 19 : 
					caos_play = load_bitmap("media/caos_sprites/19.bmp",NULL);

		;break;

		default : ;break;
		
	}

	switch(caos_enemigo){
		
		case 0 : 
					caos_playnt = load_bitmap("media/caos_sprites/caos_sprites_en/0.bmp",NULL);
		
		;break;
		
		case 1 :
					caos_playnt = load_bitmap("media/caos_sprites/caos_sprites_en/1.bmp",NULL);
		
		 ;break;
		
		case 2 : 
					caos_playnt = load_bitmap("media/caos_sprites/caos_sprites_en/2.bmp",NULL);
		
		;break;
		
		case 3 : 
					caos_playnt = load_bitmap("media/caos_sprites/caos_sprites_en/3.bmp",NULL);
		
		;break;
		
		case 4 : 
					caos_playnt = load_bitmap("media/caos_sprites/caos_sprites_en/4.bmp",NULL);
		
		;break;
		
		case 5 : 
					caos_playnt = load_bitmap("media/caos_sprites/caos_sprites_en/5.bmp",NULL);

		;break;
		
		case 6 : 
					caos_playnt = load_bitmap("media/caos_sprites/caos_sprites_en/6.bmp",NULL);
		
		;break;
		
		case 7 : 
					caos_playnt = load_bitmap("media/caos_sprites/caos_sprites_en/7.bmp",NULL);
		
		;break;
		
		case 8 :
					caos_playnt = load_bitmap("media/caos_sprites/caos_sprites_en/8.bmp",NULL);
		
		 ;break;
		
		case 9 : 
					caos_playnt = load_bitmap("media/caos_sprites/caos_sprites_en/9.bmp",NULL);
		
		;break;
		
		case 10 : 
					caos_playnt = load_bitmap("media/caos_sprites/caos_sprites_en/10.bmp",NULL);
		
		;break;
		
		case 11 : 
					caos_playnt = load_bitmap("media/caos_sprites/caos_sprites_en/11.bmp",NULL);
		
		;break;
		
		case 12 : 
					caos_playnt = load_bitmap("media/caos_sprites/caos_sprites_en/12.bmp",NULL);

		;break;
		
		case 13 : 
					caos_playnt = load_bitmap("media/caos_sprites/caos_sprites_en/13.bmp",NULL);
		
		;break;
		
		case 14 : 
					caos_playnt = load_bitmap("media/caos_sprites/caos_sprites_en/14.bmp",NULL);
		
		;break;
		
		case 15 :
					caos_playnt = load_bitmap("media/caos_sprites/caos_sprites_en/15.bmp",NULL);
		
		 ;break;
		
		case 16 : 
					caos_playnt = load_bitmap("media/caos_sprites/caos_sprites_en/16.bmp",NULL);
		
		;break;
		
		case 17 : 
					caos_playnt = load_bitmap("media/caos_sprites/caos_sprites_en/17.bmp",NULL);
		
		;break;
		
		case 18 : 
					caos_playnt = load_bitmap("media/caos_sprites/caos_sprites_en/18.bmp",NULL);
		
		;break;
		
		case 19 : 
					caos_playnt = load_bitmap("media/caos_sprites/caos_sprites_en/19.bmp",NULL);

		;break;

		default : ;break;
		
	}
}


void mostrar_caos(int caos_jugador,int caos_enemigo){
	
	
	switch(caos_jugador){
		
		case 0 : 
					caos_a = create_bitmap(50,40);
					blit(caos_play,caos_a,0,0,0,0,50,40);
					draw_sprite(batalla_fondo,caos_a,170,380);
		
		;break;
		
		case 1 :
					caos_a = create_bitmap(100,80);
					blit(caos_play,caos_a,0,0,0,0,100,80);
					draw_sprite(batalla_fondo,caos_a,170,380);
		
		 ;break;
		
		case 2 : 
					caos_a = create_bitmap(100,80);
					blit(caos_play,caos_a,0,0,0,0,100,80);
					draw_sprite(batalla_fondo,caos_a,170,380);
		
		;break;
		
		case 3 : 
					caos_a = create_bitmap(200,160);
					blit(caos_play,caos_a,0,0,0,0,200,160);
					draw_sprite(batalla_fondo,caos_a,200,400);
		
		;break;
		
		case 4 : 
					caos_a = create_bitmap(200,160);
					blit(caos_play,caos_a,0,0,0,0,200,160);
					draw_sprite(batalla_fondo,caos_a,200,400);
		
		;break;
		
		case 5 : 
					caos_a = create_bitmap(200,160);
					blit(caos_play,caos_a,0,0,0,0,200,160);
					draw_sprite(batalla_fondo,caos_a,200,400);

		;break;
		
		case 6 : 
					caos_a = create_bitmap(200,160);
					blit(caos_play,caos_a,0,0,0,0,200,160);
					draw_sprite(batalla_fondo,caos_a,200,400);
		;break;
		
		case 7 : 
					caos_a = create_bitmap(200,160);
					blit(caos_play,caos_a,0,0,0,0,200,160);
					draw_sprite(batalla_fondo,caos_a,200,400);
		;break;
		
		case 8 :
					caos_a = create_bitmap(200,160);
					blit(caos_play,caos_a,0,0,0,0,200,160);
					draw_sprite(batalla_fondo,caos_a,200,400);
		 ;break;
		
		case 9 : 
					caos_a = create_bitmap(200,160);
					blit(caos_play,caos_a,0,0,0,0,200,160);
					draw_sprite(batalla_fondo,caos_a,200,400);
		;break;
		
		case 10 : 
					caos_a = create_bitmap(200,160);
					blit(caos_play,caos_a,0,0,0,0,200,160);
					draw_sprite(batalla_fondo,caos_a,200,400);
		;break;
		
		case 11 : 
					caos_a = create_bitmap(200,160);
					blit(caos_play,caos_a,0,0,0,0,200,160);
					draw_sprite(batalla_fondo,caos_a,200,400);
		;break;
		
		case 12 : 
					caos_a = create_bitmap(200,160);
					blit(caos_play,caos_a,0,0,0,0,200,160);
					draw_sprite(batalla_fondo,caos_a,200,400);
		;break;
		
		case 13 : 
					caos_a = create_bitmap(200,160);
					blit(caos_play,caos_a,0,0,0,0,200,160);
					draw_sprite(batalla_fondo,caos_a,200,400);
		;break;
		
		case 14 : 
					caos_a = create_bitmap(200,160);
					blit(caos_play,caos_a,0,0,0,0,200,160);
					draw_sprite(batalla_fondo,caos_a,200,400);
		;break;
		
		case 15 :
					caos_a = create_bitmap(200,160);
					blit(caos_play,caos_a,0,0,0,0,200,160);
					draw_sprite(batalla_fondo,caos_a,200,400);
		 ;break;
		
		case 16 : 
					caos_a = create_bitmap(200,160);
					blit(caos_play,caos_a,0,0,0,0,200,160);
					draw_sprite(batalla_fondo,caos_a,200,400);
		;break;
		
		case 17 : 
					caos_a = create_bitmap(200,160);
					blit(caos_play,caos_a,0,0,0,0,200,160);
					draw_sprite(batalla_fondo,caos_a,200,400);
		;break;
		
		case 18 : 
					caos_a = create_bitmap(200,160);
					blit(caos_play,caos_a,0,0,0,0,200,160);
					draw_sprite(batalla_fondo,caos_a,200,400);
		;break;
		
		case 19 : 
					caos_a = create_bitmap(200,160);
					blit(caos_play,caos_a,0,0,0,0,200,160);
					draw_sprite(batalla_fondo,caos_a,200,400);
		;break;

		default : ;break;
		
	}	
	
	
	
	switch(caos_enemigo){
		
		case 0 : 
					caos_b = create_bitmap(50,40);
					blit(caos_playnt,caos_b,0,0,0,0,50,40);
					draw_sprite(batalla_fondo,caos_b,530,380);
		
		;break;
		
		case 1 :
					caos_b = create_bitmap(100,80);
					blit(caos_playnt,caos_b,0,0,0,0,100,80);
					draw_sprite(batalla_fondo,caos_b,530,380);
		
		 ;break;
		
		case 2 : 
					caos_b = create_bitmap(100,80);
					blit(caos_playnt,caos_b,0,0,0,0,100,80);
					draw_sprite(batalla_fondo,caos_b,530,380);
		
		;break;
		
		case 3 : 
					caos_b = create_bitmap(200,160);
					blit(caos_playnt,caos_b,0,0,0,0,200,160);
					draw_sprite(batalla_fondo,caos_b,530,300);
					
		
		;break;
		
		case 4 : 
					caos_b = create_bitmap(200,160);
					blit(caos_playnt,caos_b,0,0,0,0,200,160);
					draw_sprite(batalla_fondo,caos_b,530,300);
					
		
		;break;
		
		case 5 : 
					caos_b = create_bitmap(200,160);
					blit(caos_playnt,caos_b,0,0,0,0,200,160);
					draw_sprite(batalla_fondo,caos_b,530,300);
					

		;break;
		
		case 6 : 
					caos_b = create_bitmap(200,160);
					blit(caos_playnt,caos_b,0,0,0,0,200,160);
					draw_sprite(batalla_fondo,caos_b,530,300);
		
		;break;
		
		case 7 : 
					caos_b = create_bitmap(200,160);
					blit(caos_playnt,caos_b,0,0,0,0,200,160);
					draw_sprite(batalla_fondo,caos_b,530,300);
		
		;break;
		
		case 8 :
					caos_b = create_bitmap(200,160);
					blit(caos_playnt,caos_b,0,0,0,0,200,160);
					draw_sprite(batalla_fondo,caos_b,530,300);
		 ;break;
		
		case 9 : 
					caos_b = create_bitmap(200,160);
					blit(caos_playnt,caos_b,0,0,0,0,200,160);
					draw_sprite(batalla_fondo,caos_b,530,300);
		;break;
		
		case 10 : 
					caos_b = create_bitmap(200,160);
					blit(caos_playnt,caos_b,0,0,0,0,200,160);
					draw_sprite(batalla_fondo,caos_b,530,300);
		
		;break;
		
		case 11 : 
					caos_b = create_bitmap(200,160);
					blit(caos_playnt,caos_b,0,0,0,0,200,160);
					draw_sprite(batalla_fondo,caos_b,530,300);
		;break;
		
		case 12 : 
					caos_b = create_bitmap(200,160);
					blit(caos_playnt,caos_b,0,0,0,0,200,160);
					draw_sprite(batalla_fondo,caos_b,530,300);
		;break;
		
		case 13 : 
					caos_b = create_bitmap(200,160);
					blit(caos_playnt,caos_b,0,0,0,0,200,160);
					draw_sprite(batalla_fondo,caos_b,530,300);
		;break;
		
		case 14 : 
					caos_b = create_bitmap(200,160);
					blit(caos_playnt,caos_b,0,0,0,0,200,160);
					draw_sprite(batalla_fondo,caos_b,530,300);
		;break;
		
		case 15 :
					caos_b = create_bitmap(200,160);
					blit(caos_playnt,caos_b,0,0,0,0,200,160);
					draw_sprite(batalla_fondo,caos_b,530,300);
		 ;break;
		
		case 16 : 
					caos_b = create_bitmap(200,160);
					blit(caos_playnt,caos_b,0,0,0,0,200,160);
					draw_sprite(batalla_fondo,caos_b,530,300);
		;break;
		
		case 17 : 
					caos_b = create_bitmap(200,160);
					blit(caos_playnt,caos_b,0,0,0,0,200,160);
					draw_sprite(batalla_fondo,caos_b,530,300);
		;break;
		
		case 18 : 
					caos_b = create_bitmap(200,160);
					blit(caos_playnt,caos_b,0,0,0,0,200,160);
					draw_sprite(batalla_fondo,caos_b,530,300);
		;break;
		
		case 19 : 
					caos_b = create_bitmap(200,160);
					blit(caos_playnt,caos_b,0,0,0,0,200,160);
					draw_sprite(batalla_fondo,caos_b,530,300);
		;break;

		default : ;break;
		
	}	
	
	
}



void evolucion(int enemigo_conteo[20]){
	
	int aux_evo = 0;
	int i = 0;
	
	aux_evo = enemigo_conteo[i];
	
	for(i=0;i<20;i++){
		
		if(enemigo_conteo[i] < aux_evo){
			
			aux_evo = enemigo_conteo[i];
			
		}
		
	}
	
	//evolucion de etapa 0 a 1
	if(victoria > 20 && aux_evo == 0 || victoria > 20 && aux_evo == 1){
		
		caos_jugador = 1;
		
	}else if(victoria > 20 && aux_evo == 2){
		
		caos_jugador = 2;
		
	}
	
	//evolucion de etapa 1 a 2
	if(caos_jugador == 1 && victoria > 60 && aux_evo == 3){
		
		caos_jugador = 3;
		
	}else if(caos_jugador == 1 && victoria > 60 && aux_evo == 4){
		
		caos_jugador = 4;
		
	}else if(caos_jugador == 1 && victoria > 60 && aux_evo == 5){
		
		caos_jugador = 5;
		
	}else if(caos_jugador == 2 && victoria > 60 && aux_evo == 6){
		
		caos_jugador = 6;
		
	}else if(caos_jugador == 2 && victoria > 60 && aux_evo == 7){
		
		caos_jugador = 7;
		
	}else if(caos_jugador == 2 && victoria > 60 && aux_evo == 8){
		
		caos_jugador = 8;
		
	}
	
	//evolucion de tapa 2 a 3
	
	if(caos_jugador == 4 && victoria > 100 && aux_evo == 9){
		
		caos_jugador = 9;
		
	}else if(caos_jugador == 5 && victoria > 100 && aux_evo == 10){
		
		caos_jugador = 10;
		
	}else if(caos_jugador == 7 && victoria > 100 && aux_evo == 11){
		
		caos_jugador = 11;
		
	}else if(caos_jugador == 8 && victoria > 100 && aux_evo == 12){
		
		caos_jugador = 12;
		
	}
	
	//evolucion de etapa 3 a 4
	
	if(caos_jugador == 9 && victoria > 150 && aux_evo == 13){
		
		caos_jugador = 13;
		
	}else if(caos_jugador == 9 && victoria > 150 && aux_evo == 14){
		
		caos_jugador = 14;
		
	}else if(caos_jugador == 9 && victoria > 150 && aux_evo == 15){
		
		caos_jugador = 15;
		
	}else if(caos_jugador == 11 && victoria > 150 && aux_evo == 16){
		
		caos_jugador = 16;
		
	}else if(caos_jugador == 11 && victoria > 150 && aux_evo == 17){
		
		caos_jugador = 17;
		
	}else if(caos_jugador == 11 && victoria > 150 && aux_evo == 18){
		
		caos_jugador = 18;
		
	}else if(caos_jugador == 12 && victoria > 150 && aux_evo == 19){
		
		caos_jugador = 19;
		
	}
	
	
}

void registro(){
	
		int registrado = 0;
		int i = 0;
		int pos = 0;
		

				
		switch(caos_jugador){
		
		case 0 : 
					enciclopedia[0] = 1;
					
		;break;
		
		case 1 :
					enciclopedia[1] = 1;		
		 ;break;
		
		case 2 : 
					enciclopedia[2] = 1;	
		
		;break;
		
		case 3 : 
					enciclopedia[3] = 1;	
		
		;break;
		
		case 4 : 
					enciclopedia[4] = 1;	
		
		;break;
		
		case 5 : 
					enciclopedia[5] = 1;	

		;break;
		
		case 6 : 
					enciclopedia[6] = 1;	
		
		;break;
		
		case 7 : 
					enciclopedia[7] = 1;	
		
		;break;
		
		case 8 :
					enciclopedia[8] = 1;	
		
		 ;break;
		
		case 9 : 
					enciclopedia[9] = 1;	
		
		;break;
		
		case 10 : 
					enciclopedia[10] = 1;	
		
		;break;
		
		case 11 : 
					enciclopedia[11] = 1;	
		
		;break;
		
		case 12 : 
					enciclopedia[12] = 1;	

		;break;
		
		case 13 : 
					enciclopedia[13] = 1;	
		
		;break;
		
		case 14 : 
					enciclopedia[14] = 1;	
		
		;break;
		
		case 15 :
					enciclopedia[15] = 1;	
		
		 ;break;
		
		case 16 : 
					enciclopedia[16] = 1;	
		
		;break;
		
		case 17 : 
					enciclopedia[17] = 1;	
		
		;break;
		
		case 18 : 
					enciclopedia[18] = 1;	
		
		;break;
		
		case 19 : 
					enciclopedia[19] = 1;	

		;break;

		default : ;break;
		
	}
	
	for(i=0;i<20;i++){
		
		if(enciclopedia[i]==1){
			
			registrado++;
			
		}
		
	}
	
	int lapsoder = 0;
	int lapsoizq = 0;
	
	while(!key[KEY_S]){
			
			
			if(pos == 0){
				
				destroy_bitmap(reg);
				reg = load_bitmap("media/dex/dex0.bmp",NULL);
				blit(reg,screen,0,0,0,0,800,600);
				
			}			
			
			if(key[KEY_RIGHT]){
				
				
				lapsoder++;
				
				if(lapsoder == 13){
				pos++;
				lapsoder = 0;
				}
				
				if(pos == 20){
					
					pos = 19;
					
				}
				
			}
			
			if(key[KEY_LEFT]){
				
				lapsoizq++;
				
				if(lapsoizq == 13){
				pos--;
				lapsoizq = 0;
				}
			
				if(pos == -1){
					
					pos = 0;
					
				}
			}
			
			
			
			switch(pos){
				
				case 0: 
						destroy_bitmap(reg);
						reg = load_bitmap("media/dex/dex0.bmp",NULL);
						blit(reg,screen,0,0,0,0,800,600);
					
				;break;
				case 1: 
						
						if(enciclopedia[1] == 1){
						destroy_bitmap(reg);
						reg = load_bitmap("media/dex/dex1.bmp",NULL);
						blit(reg,screen,0,0,0,0,800,600);
						
						}else{
						destroy_bitmap(reg);
						reg = load_bitmap("media/dex/dexdesconocido.bmp",NULL);
						blit(reg,screen,0,0,0,0,800,600);
						}
				
				;break;
				case 2: 
						if(enciclopedia[2] == 1){
						destroy_bitmap(reg);
						reg = load_bitmap("media/dex/dex2.bmp",NULL);
						blit(reg,screen,0,0,0,0,800,600);
						
						}else{
						destroy_bitmap(reg);
						reg = load_bitmap("media/dex/dexdesconocido.bmp",NULL);
						blit(reg,screen,0,0,0,0,800,600);
						}
				
				;break;
				case 3: 
						if(enciclopedia[3] == 1){
						destroy_bitmap(reg);
						reg = load_bitmap("media/dex/dex3.bmp",NULL);
						blit(reg,screen,0,0,0,0,800,600);
						
						}else{
						destroy_bitmap(reg);
						reg = load_bitmap("media/dex/dexdesconocido.bmp",NULL);
						blit(reg,screen,0,0,0,0,800,600);
						}
				;break;
				case 4: 
						if(enciclopedia[4] == 1){
						destroy_bitmap(reg);
						reg = load_bitmap("media/dex/dex4.bmp",NULL);
						blit(reg,screen,0,0,0,0,800,600);
						
						}else{
						destroy_bitmap(reg);
						reg = load_bitmap("media/dex/dexdesconocido.bmp",NULL);
						blit(reg,screen,0,0,0,0,800,600);
						}
				;break;
				case 5: 
						if(enciclopedia[5] == 1){
						destroy_bitmap(reg);
						reg = load_bitmap("media/dex/dex5.bmp",NULL);
						blit(reg,screen,0,0,0,0,800,600);
						
						}else{
						destroy_bitmap(reg);
						reg = load_bitmap("media/dex/dexdesconocido.bmp",NULL);
						blit(reg,screen,0,0,0,0,800,600);
						}
				;break;
				case 6: 
						if(enciclopedia[6] == 1){
						destroy_bitmap(reg);
						reg = load_bitmap("media/dex/dex6.bmp",NULL);
						blit(reg,screen,0,0,0,0,800,600);
						
						}else{
						destroy_bitmap(reg);
						reg = load_bitmap("media/dex/dexdesconocido.bmp",NULL);
						blit(reg,screen,0,0,0,0,800,600);
						}
				;break;
				case 7: 
						if(enciclopedia[7] == 1){
						destroy_bitmap(reg);
						reg = load_bitmap("media/dex/dex7.bmp",NULL);
						blit(reg,screen,0,0,0,0,800,600);
						
						}else{
						destroy_bitmap(reg);
						reg = load_bitmap("media/dex/dexdesconocido.bmp",NULL);
						blit(reg,screen,0,0,0,0,800,600);
						}
				;break;
				case 8: 
						if(enciclopedia[8] == 1){
						destroy_bitmap(reg);
						reg = load_bitmap("media/dex/dex8.bmp",NULL);
						blit(reg,screen,0,0,0,0,800,600);
						
						}else{
						destroy_bitmap(reg);
						reg = load_bitmap("media/dex/dexdesconocido.bmp",NULL);
						blit(reg,screen,0,0,0,0,800,600);
						}
				;break;
				case 9: 
						if(enciclopedia[9] == 1){
						destroy_bitmap(reg);
						reg = load_bitmap("media/dex/dex9.bmp",NULL);
						blit(reg,screen,0,0,0,0,800,600);
						
						}else{
						destroy_bitmap(reg);
						reg = load_bitmap("media/dex/dexdesconocido.bmp",NULL);
						blit(reg,screen,0,0,0,0,800,600);
						}
				;break;
				case 10: 
						if(enciclopedia[10] == 1){
						destroy_bitmap(reg);
						reg = load_bitmap("media/dex/dex10.bmp",NULL);
						blit(reg,screen,0,0,0,0,800,600);
						
						}else{
						destroy_bitmap(reg);
						reg = load_bitmap("media/dex/dexdesconocido.bmp",NULL);
						blit(reg,screen,0,0,0,0,800,600);
						}
				;break;
				case 11: 
						if(enciclopedia[11] == 1){
						destroy_bitmap(reg);
						reg = load_bitmap("media/dex/dex11.bmp",NULL);
						blit(reg,screen,0,0,0,0,800,600);
						
						}else{
						destroy_bitmap(reg);
						reg = load_bitmap("media/dex/dexdesconocido.bmp",NULL);
						blit(reg,screen,0,0,0,0,800,600);
						}
				;break;
				case 12: 
						if(enciclopedia[12] == 1){
						destroy_bitmap(reg);
						reg = load_bitmap("media/dex/dex12.bmp",NULL);
						blit(reg,screen,0,0,0,0,800,600);
						
						}else{
						destroy_bitmap(reg);
						reg = load_bitmap("media/dex/dexdesconocido.bmp",NULL);
						blit(reg,screen,0,0,0,0,800,600);
						}
				;break;
				case 13: 
						if(enciclopedia[13] == 1){
						destroy_bitmap(reg);
						reg = load_bitmap("media/dex/dex13.bmp",NULL);
						blit(reg,screen,0,0,0,0,800,600);
						
						}else{
						destroy_bitmap(reg);
						reg = load_bitmap("media/dex/dexdesconocido.bmp",NULL);
						blit(reg,screen,0,0,0,0,800,600);
						}
				;break;
				case 14: 
						if(enciclopedia[14] == 1){
						destroy_bitmap(reg);
						reg = load_bitmap("media/dex/dex14.bmp",NULL);
						blit(reg,screen,0,0,0,0,800,600);
						
						}else{
						destroy_bitmap(reg);
						reg = load_bitmap("media/dex/dexdesconocido.bmp",NULL);
						blit(reg,screen,0,0,0,0,800,600);
						}
				;break;
				case 15: 
						if(enciclopedia[15] == 1){
						destroy_bitmap(reg);
						reg = load_bitmap("media/dex/dex15.bmp",NULL);
						blit(reg,screen,0,0,0,0,800,600);
						
						}else{
						destroy_bitmap(reg);
						reg = load_bitmap("media/dex/dexdesconocido.bmp",NULL);
						blit(reg,screen,0,0,0,0,800,600);
						}
				;break;
				case 16: 
						if(enciclopedia[16] == 1){
						destroy_bitmap(reg);
						reg = load_bitmap("media/dex/dex16.bmp",NULL);
						blit(reg,screen,0,0,0,0,800,600);
						
						}else{
						destroy_bitmap(reg);
						reg = load_bitmap("media/dex/dexdesconocido.bmp",NULL);
						blit(reg,screen,0,0,0,0,800,600);
						}
				;break;
				case 17: 
						if(enciclopedia[17] == 1){
						destroy_bitmap(reg);
						reg = load_bitmap("media/dex/dex17.bmp",NULL);
						blit(reg,screen,0,0,0,0,800,600);
						
						}else{
						destroy_bitmap(reg);
						reg = load_bitmap("media/dex/dexdesconocido.bmp",NULL);
						blit(reg,screen,0,0,0,0,800,600);
						}
				;break;
				case 18: 
						if(enciclopedia[18] == 1){
						destroy_bitmap(reg);
						reg = load_bitmap("media/dex/dex18.bmp",NULL);
						blit(reg,screen,0,0,0,0,800,600);
						
						}else{
						destroy_bitmap(reg);
						reg = load_bitmap("media/dex/dexdesconocido.bmp",NULL);
						blit(reg,screen,0,0,0,0,800,600);
						}
				;break;
				case 19: 
						if(enciclopedia[19] == 1){
						destroy_bitmap(reg);
						reg = load_bitmap("media/dex/dex19.bmp",NULL);
						blit(reg,screen,0,0,0,0,800,600);
						
						}else{
						destroy_bitmap(reg);
						reg = load_bitmap("media/dex/dexdesconocidofinal.bmp",NULL);
						blit(reg,screen,0,0,0,0,800,600);
						}
				;break;
				default: ;break;
				
				
				
				
				
				
				
				
				
				
			}
			
			
		}
		
			puntaje = registrado *100 + (victoria * 100);
		
			//agregar nombre uwu
	
	
	
	
	
}



