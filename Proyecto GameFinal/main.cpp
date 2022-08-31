#include<allegro.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<unistd.h>

struct caotyks
{
	char nombre[20]; //Nombre del Monstruo
	char tipo[10]; //atributo principal "vacuna,data,virus"
	char tipo_b[10]; //atributo secundario "fuego,agua,hierba" o "madera,trueno,acero
	int atk; //ataque base
	int def; // defensa base
	int vida; // vida base
}caos[20];

struct puntosfinal
{//estructura de datos con entrada y salida txt para el ranking
	char nombre[3];//nombre de player maximo 3 caracteres
	int puntos;// puntaje final
}puntitos[4];

void inicio();//funcion que inicia allegro
void caotyks_inicio(); // funcion que carga el monstruo del jugador y el del enemigo con entrada txt
void fondo();//funcion que muestra el mapa en pantalla 800x600
void _menu();//funcion de los 2 menus del inicio del juego
void movimiento();//Funcion encargada del movimiento del jugador
void batalla_carga();//funcion que hace funcional la funcion "batalla()"
void batalla();//funcion encargada de todo el sistema de combate
void loadspr(int caos_jugador,int caos_enemigo);//funcion que carga los sprites de los monstruos en combate dependiendo de 2 valores entregados
void mostrar_caos(int caos_jugador,int caos_enemigo);//funcion que muestra los sprites ya cargados dependiendo de las funciones anteriores
void evolucion(int enemigo_conteo[20]);//funcion encargada del avance, dificultad y transformacion del monstruo del jugador
void registro();//funcion que registra el puntaje obtenido
void ranking();//funcion que se encarga de ordenar y mostrar el puntaje en forma de ranking

//CREACION DE BITMAPS PARA LA VISUALIZACION DEL JUEGO
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
//CREACION DE SAMPLES PARA LA REPRODUCCION DE SONIDO DENTRO DEL JUEGO
SAMPLE *musicfondo;
SAMPLE *musicbatalla;

//==========================================Variables Globales===================
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
//===============================================================================

void main()
{
	int i = 0;//Variable encargada del ciclo for de la Enciclopedia
	srand(time(NULL));
	caotyks_inicio();
	inicio();
	_menu();
	fondo();
	
	for(i=0;i<20;i++)
	{
		enciclopedia[i] = 0;
	}//Ciclo for que se encarga de la inicializacion de la enciclopedia para su uso
	while(!key[KEY_ESC])
	{
		movimiento();
	}//Ciclo While encargado del correcto funcionamiento del juego
	
	//Destruccion de BITMAPS al finalizar el juego
	destroy_bitmap(menu);
	destroy_bitmap(bmp);
	destroy_bitmap(batalla_fondo);
	destroy_bitmap(chr);
	destroy_bitmap(pjaba);
	destroy_bitmap(pjder);
	destroy_bitmap(pjarr);
	destroy_bitmap(pjizq);
	destroy_bitmap(caos_play);
	destroy_bitmap(caos_playnt);
	destroy_bitmap(caos_a);
	destroy_bitmap(caos_b);
	destroy_bitmap(reg);
	allegro_exit();
}
END_OF_MAIN();

void inicio()//Funcion encargada del inicio de todas las funciones de allegro
{
	allegro_init();
	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
	install_keyboard();
	install_mouse();
	install_timer();
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0);
}

void movimiento()//Todo lo relacionado con el movimiento libre del jugador y la visualizacion de tal y su entorno
{
	//Impresion en pantalla de las victorias y derrotas del jugador
	textprintf_ex(screen, font, 50,50, makecol(0, 0, 0),-1, "VICTORIAS : %d",victoria);
	textprintf_ex(screen, font, 50,60, makecol(0, 0, 0),-1, "DERROTAS : %d",derrota);
	
	if(aux_conteo == 0)//Condicion encargada de la aparicion al azar de combates a medida que se avanza
	{
		numconteo = 1 + rand() % ((250+1)-1);
		aux_conteo = 1;	
	}
	
	destroy_bitmap(bmp);//destruccion de bitmap para la liberacion de memoria ya que es un ciclo constante "movimiento()"

	if(key[KEY_Q])//Cadena de IF encarcaga del cambio de mapas dependiendo de 2 variables: tecla y valor de victoria
	{
		mapa = 0;//mapa pradera 1
	}else if(key[KEY_W] && victoria > 20)
	{
		mapa = 1;//mapa pradera 2
	}else if(key[KEY_E] && victoria >60)
	{
		mapa = 2;//mapa circuito
	}else if(key[KEY_R] && victoria >60)
	{
		mapa = 3;//mapa cueva
	}
	//==============================================================================================================			
	switch(mapa)//Switch encargado de cargar los mapas segun la cadena de sentencia de IF anterior
	{				
		case 0 : bmp = load_bitmap("media/fondo.bmp",NULL);break;
		case 1 : bmp = load_bitmap("media/fondo2.bmp",NULL);break;
		case 2 : bmp = load_bitmap("media/fondo3.bmp",NULL);break;
		case 3 : bmp = load_bitmap("media/fondo4.bmp",NULL);break;
		default : bmp = load_bitmap("media/fondo.bmp",NULL);break;				
	}
		
	if(key[KEY_LEFT] && !key[KEY_UP] && !key[KEY_DOWN] && !key[KEY_RIGHT] && player_x > 15)//sentencia if encargada del movimiento y limite hacia la izquierda
	{				
		blit(pjizq,chr,0,0,0,0,32,42);//impresion de un bitmap dentro de otro (el personaje)
		draw_sprite(bmp,chr,player_x,player_y);	//dibujar el bitmap anterior en pantalla (el personaje en pantalla)
		player_x = player_x - 1; //movimiento hacia la izquierda
	
		if(key[KEY_X])//sentencia if encargada de la accion de "Correr"
		{
			player_x = player_x - 2;
		}
		
		conteo ++;//conteo de los "pasos" para la funcion de batalla
		batalla();//segun la variable "conteo" se entra a la primera parte de la funcion de batalla
		blit(bmp,screen,0,0,0,0,800,600);//se imprime la pantalla nuevamente (el mapa) tras salir de combate
	}
			
	if(key[KEY_RIGHT] && !key[KEY_UP] && !key[KEY_DOWN] && !key[KEY_LEFT] && player_x < 750)//sentencia if encargada del movimiento y limite hacia la derecha
	{//se repite lo de la sentencia de if de arriba solo que con algunos cambios en las variables
		blit(pjder,chr,0,0,0,0,32,42);
		draw_sprite(bmp,chr,player_x,player_y);
		player_x = player_x + 1;
				
		if(key[KEY_X])
		{
			player_x = player_x + 2;	
		}
	
		conteo ++;
		batalla();
		blit(bmp,screen,0,0,0,0,800,600);
	}
			
	if(key[KEY_UP] && !key[KEY_LEFT] && !key[KEY_DOWN] && !key[KEY_RIGHT] && player_y > 15)//sentencia If encargada del movimiento y limite hacia arriba
	{//se repite lo de la sentencia de if de arriba solo que con algunos cambios en las variables
		blit(pjarr,chr,0,0,0,0,32,42);
		draw_sprite(bmp,chr,player_x,player_y);
		player_y = player_y - 1;
		
		if(key[KEY_X])
		{
			player_y = player_y - 2;	
		}
		
		conteo ++;
		batalla();
		blit(bmp,screen,0,0,0,0,800,600);
	}
			
	if(key[KEY_DOWN] && !key[KEY_UP] && !key[KEY_LEFT] && !key[KEY_RIGHT] && player_y < 540)//sentencia If encargada del movimiento y limite hacia abajo
	{//se repite lo de la sentencia de if de arriba solo que con algunos cambios en las variables
		blit(pjaba,chr,0,0,0,0,32,42);
		draw_sprite(bmp,chr,player_x,player_y);
		player_y = player_y + 1;
				
		if(key[KEY_X])
		{	
			player_y = player_y + 2;	
		}
		
		conteo ++;
		batalla();
		blit(bmp,screen,0,0,0,0,800,600);		
	}
		//Sentencia IF encargada de la carga de la carga y visualizacion de la ENCICLOPEDIA	
		if(key[KEY_A])
		{
			registro();
		}
		//==================================================================================
	
		draw_sprite(bmp,chr,player_x,player_y);
		blit(bmp,screen,0,0,0,0,800,600);
		//se finaliza la funcion con la impresion de la posicion actual del jugador y la impresion del mapa
}

void _menu()//funcion encargada de los 2 menus del inicio
{
	//carga del menu principal y la musica a usarse
	menu = load_bitmap("media/menu.bmp",NULL);
	musicfondo = load_sample("media/sonidos/fondo.wav");
	musicbatalla = load_sample("media/sonidos/batalla.wav");
	
	do
	{
		blit(menu,screen,0,0,0,0,800,600);//impresion del 1er menu
		
		if(key[KEY_ENTER])//impresion del segundo menu "tutorial" si se cumple la condicion
		{
			menu = load_bitmap("media/menu2.bmp",NULL);
			blit(menu,screen,0,0,0,0,800,600);
		}
		if(key[KEY_ESC]){//Salida del juego desde cualquiera de los 2 menus
			
			allegro_exit();
		}	
		
	}while(!key[KEY_Z]);//se cumple todo dentro del Do hasta que se presione la tecla Z

	destroy_bitmap(menu);//se libera el bitmap del menu ya que no se usara mas
}

void fondo()//carga de la animacion del personaje al mirar en diferentes direcciones y creacion de bitmaps de este mismo junto a la pantalla
{
	bmp = create_bitmap(800, 600);//bitmap donde se desarrolla el movimiento
	chr = create_bitmap(32,42);//bitmap del personaje

	//Carga de las diferentes animacion del personaje
	pjaba = load_bitmap("media/JymAba.bmp",NULL);
	pjarr = load_bitmap("media/JymArr.bmp",NULL);
	pjizq = load_bitmap("media/JymIzq.bmp",NULL);
	pjder = load_bitmap("media/JymDer.bmp",NULL);
	//=============================================
	blit(pjaba,chr,0,0,0,0,32,42);	
	draw_sprite(bmp,chr,player_x,player_y);
	//se finaliza con la carga e impresion del personaje
}

void caotyks_inicio()//funcion encargada de la entrada de variables mediante archivo txt, se encarga de la inicializacion de los Caotyks
{
	int i = 0;//contador
	FILE *enemigos;//creacion de un archivo FILE
	enemigos = fopen("caotyks.txt","rt");// se ingresa al archivo FILE "enemigos" un archivo txt, en este caso rt (read text)
	
	for(i=0;i<20;i++)//ciclo de guardado de variables en una estructura ya declarada de manera global
	{
		fscanf(enemigos,"%s ",caos[i].nombre);
		fscanf(enemigos,"%s ",caos[i].tipo);
		fscanf(enemigos,"%s ",caos[i].tipo_b);
		fscanf(enemigos,"%d ",&caos[i].atk);
		fscanf(enemigos,"%d ",&caos[i].def);
		fscanf(enemigos,"%d",&caos[i].vida);
	}
	fclose (enemigos);//cierre del archivo una vez ya utilizado
}
//======================================================================================================================================
void batalla()//FUNCION DE CONTEO DE BATALLA
{
	if(conteo == numconteo)//si el conteo de los pasos es igual al conteo de los combates al azar, comienza el combate
	{
		batalla_carga();//funcion del combate
		conteo = 0;//se inicializa nuevamente el contador a 0 despues de la batalla
	}
}
//======================================================================================================================================
 void batalla_carga()
 {
	int opcion[2];//arreglo encargado de las opciones dentro del combate, 0 pocion, 1 atacar, 2 escapar
	//Inicializacion de variables de combate para iniciar con la opcion en atacar
	opcion[0] = 0;//pocion - inactivo "0"
	opcion[1] = 1;//atacar - activo "1"
	opcion[2] = 0;//escapar - inactivo "0"
	
	//VARIABLES LOCALES
	int caos_enemigo = 0;//variable encargada de determinar enemigo
	int damage_player = 0;//daño realizado por el jugador
	int damage_enemy = 0;//daño realizado por el enemigo
	int aux_vida = 0;//auxiliar de vida para guardar el valor de la vida maxima del jugador
	int aux_vida_e = 0;//auxiliar de vida para guardar el valor de la vida maxima del enemigo
	int pocion = 3;//cantidad de pociones maximas, despues de cada uso en combate se inicializa nuevamente en 3
	int enemigo_conteo[20];//arreglo encargado de llevar la cuenta de a que enemigo te enfrentas y GANAS
	int i = 0;//contador
	//=====================
	
	for(i=0;i<20;i++)//ciclo encargado de inicializar el arreglo local
	{
		enemigo_conteo[i] = 0;
	}
	
	in_battle = 1;//estima si estas en combate o no, 1 SI, 2 NO
	
	//Sentencias de IF encargadas de la dificultad del juego===============================================================
	if(caos_jugador == 0 && mapa == 0 || mapa == 1)//modo facil
	{
		caos_enemigo = 0 + rand() % ((3+1)-1);
		
	}else if(caos_jugador <= 6 && mapa == 0 || mapa == 1)//modo intermedio
	{
		caos_enemigo = 1 + rand() % ((8+1)-1);
		
	}else if(caos_jugador <=13 && mapa == 2 || mapa == 3)//modo intermedio-dificil
	{
		caos_enemigo = 1 + rand() % ((12+1)-1);
		
	}else if(caos_jugador <=20 && mapa == 3)//modo dificil
	{ 
		caos_enemigo = 1 + rand() % ((18+1)-1);
		
		if(caos_enemigo > 20)//Una restriccion para no superar el numero maximo de cantidad de caotyks disponibles
		{
			caos_enemigo = 19;
		}
		
	}
	//=====================================================================================================================
	aux_vida = caos[caos_jugador].vida;//guarda el valor de la vida maxima del jugador para recuperarla despues de combate
	aux_vida_e = caos[caos_enemigo].vida;//guarda el valor de la vida maxima del enemigo para recuperarla despues de combate
	destroy_bitmap(batalla_fondo);//libera el bitmap para reutilizarlo nuevamente

	//carga de la batalla en opcion Atacar
	if(mapa == 0)
	{
		batalla_fondo = load_bitmap("media/batalla1.bmp",NULL);	
	}else if(mapa == 1)
	{
		batalla_fondo = load_bitmap("media/batalla1.bmp",NULL);	
	}else if(mapa == 2)
	{
		batalla_fondo = load_bitmap("media/batallacircuito1.bmp",NULL);	
	}else if(mapa == 3)
	{
		batalla_fondo = load_bitmap("media/batallacueva1.bmp",NULL);	
	}
	//===================================

	//funciones para cargar y mostrar el caos del jugador y enemigo
	loadspr(caos_jugador,caos_enemigo);
	mostrar_caos(caos_jugador,caos_enemigo);
	//=============================================================
	do
	{
		blit(batalla_fondo,screen,0,0,0,0,800,600);
		
		if(opcion[0] == 0 && opcion[1] == 1 && opcion[2] == 0)//SI SE CAMBIA A LA OPCION ATACAR
		{	
			destroy_bitmap(batalla_fondo);//libera bitmap para reutilizar
			
			if(mapa == 0)//ciclo if encargado de mostrar cada escenario dependiendo del mapa
			{
				batalla_fondo = load_bitmap("media/batalla1.bmp",NULL);
			}else if(mapa == 1)
			{
				batalla_fondo = load_bitmap("media/batalla1.bmp",NULL);
			}else if(mapa == 2)
			{
				batalla_fondo = load_bitmap("media/batallacircuito1.bmp",NULL);
			}else if(mapa == 3)
			{
				batalla_fondo = load_bitmap("media/batallacueva1.bmp",NULL);
			}
			//===============================================================================
			//IMPRESION DE DATOS EN PANTALLA MEDIANTE UN PRINTF
			textprintf_ex(batalla_fondo, font, 50, 210, makecol(0, 0, 0),-1, "%d / %d", aux_vida,caos[caos_jugador].vida);//vida jugador
			textprintf_ex(batalla_fondo, font, 650, 210, makecol(0, 0, 0),-1, "%d / %d", aux_vida_e,caos[caos_enemigo].vida);//vida enemigo
			textprintf_ex(batalla_fondo, font, 75, 190, makecol(0, 0, 0),-1, "%s",caos[caos_jugador].nombre);//nombre caotyk jugador
			textprintf_ex(batalla_fondo, font, 670, 190, makecol(0, 0, 0),-1, "%s",caos[caos_enemigo].nombre);//nombre caotyk enemigo
			textprintf_ex(batalla_fondo, font, 210, 55, makecol(0, 0, 0),-1, "X %d", pocion);//cantidad de pociones
			//=================================================
			mostrar_caos(caos_jugador,caos_enemigo);//muestra nuevamente al enemigo en pantalla para su correcta visualizacion (sino parpadea)
			blit(batalla_fondo,screen,0,0,0,0,800,600);//impresion de pantalla
	
			if(key[KEY_Z])//SI SE DECIDE ATACAR
			{
				if(caos[caos_jugador].tipo == caos[caos_enemigo].tipo || caos[caos_jugador].tipo_b == caos[caos_enemigo].tipo_b )//teniendo 1 TIPO IGUAL
				{
					//DAÑO DE JUGADOR
					damage_player = (caos[caos_jugador].atk * 1.2) - caos[caos_enemigo].def;
					aux_vida_e = aux_vida_e - damage_player;
					//DAÑO DE ENEMIGO
					damage_enemy = (caos[caos_enemigo].atk * 1.2) - caos[caos_jugador].def;
					aux_vida = aux_vida - damage_enemy;
					//INICIALIZACION NUEVAMENTE DEL DAÑO EN 0
					damage_player = 0;
					damage_enemy = 0;		
				}
				
				if(caos[caos_jugador].tipo == caos[caos_enemigo].tipo && caos[caos_jugador].tipo_b == caos[caos_enemigo].tipo_b)//teniendo 2 TIPOS IGUALES
				{
					//DAÑO DE JUGADOR
					damage_player = caos[caos_jugador].atk - (caos[caos_enemigo].def / 2);
					aux_vida_e = aux_vida_e - damage_player;
					//DAÑO DE ENEMIGO
					damage_enemy = caos[caos_enemigo].atk - (caos[caos_jugador].def / 2);
					aux_vida = aux_vida - damage_enemy;
					//INICIALIZACION NUEVAMENTE DEL DAÑO EN 0
					damage_player = 0;
					damage_enemy = 0;	
				}
				
				if(caos[caos_jugador].tipo != caos[caos_enemigo].tipo && caos[caos_jugador].tipo_b != caos[caos_enemigo].tipo_b)//NINGUN TIPO IGUAL
				{
					//DAÑO DE JUGADOR
					damage_player = caos[caos_jugador].atk - caos[caos_enemigo].def;
					aux_vida_e = aux_vida_e - damage_player;
					//DAÑO DE ENEMIGO
					damage_enemy = caos[caos_enemigo].atk - caos[caos_jugador].def;
					aux_vida = aux_vida - damage_enemy;
					//INICIALIZACION DE DAÑO EN 0
					damage_player = 0;
					damage_enemy = 0;
				}
				
				if(aux_vida_e <= 0 || aux_vida <= 0)// SI MUERE EL JUGADOR O EL ENEMIGO
				{
					if(aux_vida_e <= 0)//SI MUERE EL ENEMIGO
					{
						victoria++;//CONTADOR DE VICTORIA
						enemigo_conteo[caos_enemigo] ++;//CONTADOR DE QUE ENEMIGO FUE DERROTADO
					}else if(aux_vida <= 0)// SI SE MUERE EL JUGADOR
					{
						derrota++;//CONTADOR DE DERROTA
						caos_jugador --;//reduce caos por muerte
						
						if(caos_jugador>0)//limitador de reductor de caos
						{
							caos_jugador = 0;
						}
						
					}
					
					in_battle = 0;//SE SALE DEL COMBATE
					aux_vida = 0;//SE INICIALIZA EN 0 PARA REUTILIZAR
					aux_vida_e = 0;//SE INICIALIZA EN 0 PARA REUTILIZAR
				}
			}
			
			if(key[KEY_LEFT])//SE VA A OPCION DE POCION
			{
				opcion[1] = 0;
				opcion[0] = 1;
			}else if(key[KEY_RIGHT])//SE VA A OPCION DE ESCAPAR
			{
				opcion[1] = 0;
				opcion[2] = 1;
			}
		}
		
		if(opcion[0] == 1 && opcion[1] == 0 && opcion[2] == 0)//SE CAMBIA LA OPCION A POCION
		{
			
			destroy_bitmap(batalla_fondo);//se libera bitmap para reutilizar
		
			if(mapa == 0)//ciclo if encargado de mostrar cada escenario dependiendo del mapa
			{
				batalla_fondo = load_bitmap("media/batalla0.bmp",NULL);		
			}else if(mapa == 1)
			{
				batalla_fondo = load_bitmap("media/batalla0.bmp",NULL);	
			}else if(mapa == 2)
			{
				batalla_fondo = load_bitmap("media/batallacircuito0.bmp",NULL);	
			}else if(mapa == 3)
			{
				batalla_fondo = load_bitmap("media/batallacueva0.bmp",NULL);	
			}
			//=============================================================================
			//impresion nuevamente de texto en pantalla VER EN ATACAR
			textprintf_ex(batalla_fondo, font, 50, 210, makecol(0, 0, 0),-1, "%d / %d", aux_vida,caos[caos_jugador].vida);
			textprintf_ex(batalla_fondo, font, 650, 210, makecol(0, 0, 0),-1, "%d / %d", aux_vida_e,caos[caos_enemigo].vida);
			textprintf_ex(batalla_fondo, font, 75, 190, makecol(0, 0, 0),-1, "%s",caos[caos_jugador].nombre);
			textprintf_ex(batalla_fondo, font, 670, 190, makecol(0, 0, 0),-1, "%s",caos[caos_enemigo].nombre);
			textprintf_ex(batalla_fondo, font, 210, 55, makecol(0, 0, 0),-1, "X %d", pocion);
			//=======================================================
		
			mostrar_caos(caos_jugador,caos_enemigo);//muestra nuevamente los enemigos VER ATACAR
			blit(batalla_fondo,screen,0,0,0,0,800,600);//impresion de pantalla
					
			if(key[KEY_Z])// SI SE SELECCIONA EL USAR POCION
			{
				while(aux_vida < caos[caos_jugador].vida && pocion != 0)//VERIFICA QUE TE FALTE VIDA Y QUE TE QUEDEN POCIONES
				{
					aux_vida = aux_vida + 1000;//RECARGA 1000 DE VIDA
					
					if(aux_vida > caos[caos_jugador].vida)// RESTRICCION PARA TENER UN LIMITE MAXIMO QUE ES LA VIDA MAXIMA AL CURAR
					{
						aux_vida = caos[caos_jugador].vida; 
					}
					
					pocion--;//SE RESTRA 1 POCION EN COMBATE
				}
			}
					
			if(key[KEY_RIGHT])//SE CAMBIA A ESCAPAR
			{
				opcion[0] = 0;
				opcion[2] = 1;
			}else if(key[KEY_DOWN])//SE CAMBIA A ATACAR
			{
				opcion[0] = 0;
				opcion[1] = 1;
				opcion[2] = 0;
			}
		}
		
		if(opcion[0] == 0 && opcion[1] == 0 && opcion[2] == 1)//SELECCIONA ESCAPAR
		{
			destroy_bitmap(batalla_fondo);//liberacion de bitmap para reutilizar
		
			if(mapa == 0)//ciclo if encargado de mostrar cada escenario dependiendo del mapa
			{
				batalla_fondo = load_bitmap("media/batalla2.bmp",NULL);	
			}else if(mapa == 1)
			{
				batalla_fondo = load_bitmap("media/batalla2.bmp",NULL);
			}else if(mapa == 2)
			{
				batalla_fondo = load_bitmap("media/batallacircuito2.bmp",NULL);
			}else if(mapa == 3)
			{
				batalla_fondo = load_bitmap("media/batallacueva2.bmp",NULL);
			}
			//==============================================================================
			//Impresion de datos en la pantalla en combate VER ATACAR
			textprintf_ex(batalla_fondo, font, 50, 210, makecol(0, 0, 0),-1, "%d / %d", aux_vida,caos[caos_jugador].vida);
			textprintf_ex(batalla_fondo, font, 650, 210, makecol(0, 0, 0),-1, "%d / %d", aux_vida_e,caos[caos_enemigo].vida);
			textprintf_ex(batalla_fondo, font, 75, 190, makecol(0, 0, 0),-1, "%s",caos[caos_jugador].nombre);
			textprintf_ex(batalla_fondo, font, 670, 190, makecol(0, 0, 0),-1, "%s",caos[caos_enemigo].nombre);
			textprintf_ex(batalla_fondo, font, 210, 55, makecol(0, 0, 0),-1, "X %d", pocion);
			//========================================================
			mostrar_caos(caos_jugador,caos_enemigo);//muestra nuevamente a los caotyks VER ATACAR
			blit(batalla_fondo,screen,0,0,0,0,800,600);//impresion de pantalla
							
			if(key[KEY_Z])//SI SE DECIDE ESCAPAR
			{
				in_battle = 0;// TERMINA COMBATE
				aux_vida = 0;//SE INICIALIZA AUX DE VIDA
				aux_vida_e = 0;//SE INICIALIZA AUX DE VIDA DE ENEMIGO
			}else if(key[KEY_LEFT])//CAMBIA A POCION
			{
				opcion[0] = 1;
				opcion[2] = 0;
				
			}else if(key[KEY_DOWN])//CAMBIA A ATACAR
			{
				opcion[0] = 0;
				opcion[1] = 1;
				opcion[2] = 0;
			}
		}
	}while(in_battle == 1);//TODO ESTO SE CUMPLIRA MIENTRAS SE ESTE EN COMBATE, OSEA in_battle == 1
	
	evolucion(enemigo_conteo); //Funcion encargada de la evolucion del caotyk del jugador dependiendo de las batallas
}

void loadspr(int caos_jugador,int caos_enemigo)//FUNCION ENCARGADA DE LA CARGA DE LAS IMAGENES DE LOS ENEMIGOS
{
	switch(caos_jugador)//CARGA DE IMAGENES DEL CAOTYK JUGADOR
	{
		case 0 : caos_play = load_bitmap("media/caos_sprites/0.bmp",NULL);break;
		case 1 : caos_play = load_bitmap("media/caos_sprites/1.bmp",NULL);break;
		case 2 : caos_play = load_bitmap("media/caos_sprites/2.bmp",NULL);break;
		case 3 : caos_play = load_bitmap("media/caos_sprites/3.bmp",NULL);break;
		case 4 : caos_play = load_bitmap("media/caos_sprites/4.bmp",NULL);break;
		case 5 : caos_play = load_bitmap("media/caos_sprites/5.bmp",NULL);break;
		case 6 : caos_play = load_bitmap("media/caos_sprites/6.bmp",NULL);break;
		case 7 : caos_play = load_bitmap("media/caos_sprites/7.bmp",NULL);break;
		case 8 : caos_play = load_bitmap("media/caos_sprites/8.bmp",NULL);break;
		case 9 : caos_play = load_bitmap("media/caos_sprites/9.bmp",NULL);break;
		case 10 : caos_play = load_bitmap("media/caos_sprites/10.bmp",NULL);break;
		case 11 : caos_play = load_bitmap("media/caos_sprites/11.bmp",NULL);break;
		case 12 : caos_play = load_bitmap("media/caos_sprites/12.bmp",NULL);break;
		case 13 : caos_play = load_bitmap("media/caos_sprites/13.bmp",NULL);break;
		case 14 : caos_play = load_bitmap("media/caos_sprites/14.bmp",NULL);break;
		case 15 : caos_play = load_bitmap("media/caos_sprites/15.bmp",NULL);break;
		case 16 : caos_play = load_bitmap("media/caos_sprites/16.bmp",NULL);break;
		case 17 : caos_play = load_bitmap("media/caos_sprites/17.bmp",NULL);break;
		case 18 : caos_play = load_bitmap("media/caos_sprites/18.bmp",NULL);break;
		case 19 : caos_play = load_bitmap("media/caos_sprites/19.bmp",NULL);break;
		default : ;break;
	}

	switch(caos_enemigo)//CARGA DE IMAGENES DE CAOTYK ENEMIGO
	{
		case 0 : caos_playnt = load_bitmap("media/caos_sprites/caos_sprites_en/0.bmp",NULL);break;
		case 1 : caos_playnt = load_bitmap("media/caos_sprites/caos_sprites_en/1.bmp",NULL);break;
		case 2 : caos_playnt = load_bitmap("media/caos_sprites/caos_sprites_en/2.bmp",NULL);break;
		case 3 : caos_playnt = load_bitmap("media/caos_sprites/caos_sprites_en/3.bmp",NULL);break;
		case 4 : caos_playnt = load_bitmap("media/caos_sprites/caos_sprites_en/4.bmp",NULL);break;
		case 5 : caos_playnt = load_bitmap("media/caos_sprites/caos_sprites_en/5.bmp",NULL);break;
		case 6 : caos_playnt = load_bitmap("media/caos_sprites/caos_sprites_en/6.bmp",NULL);break;
		case 7 : caos_playnt = load_bitmap("media/caos_sprites/caos_sprites_en/7.bmp",NULL);break;
		case 8 : caos_playnt = load_bitmap("media/caos_sprites/caos_sprites_en/8.bmp",NULL);break;
		case 9 : caos_playnt = load_bitmap("media/caos_sprites/caos_sprites_en/9.bmp",NULL);break;
		case 10 : caos_playnt = load_bitmap("media/caos_sprites/caos_sprites_en/10.bmp",NULL);break;
		case 11 : caos_playnt = load_bitmap("media/caos_sprites/caos_sprites_en/11.bmp",NULL);break;
		case 12 : caos_playnt = load_bitmap("media/caos_sprites/caos_sprites_en/12.bmp",NULL);break;
		case 13 : caos_playnt = load_bitmap("media/caos_sprites/caos_sprites_en/13.bmp",NULL);break;
		case 14 : caos_playnt = load_bitmap("media/caos_sprites/caos_sprites_en/14.bmp",NULL);break;
		case 15 : caos_playnt = load_bitmap("media/caos_sprites/caos_sprites_en/15.bmp",NULL);break;
		case 16 : caos_playnt = load_bitmap("media/caos_sprites/caos_sprites_en/16.bmp",NULL);break;
		case 17 : caos_playnt = load_bitmap("media/caos_sprites/caos_sprites_en/17.bmp",NULL);break;
		case 18 : caos_playnt = load_bitmap("media/caos_sprites/caos_sprites_en/18.bmp",NULL);break;
		case 19 : caos_playnt = load_bitmap("media/caos_sprites/caos_sprites_en/19.bmp",NULL);break;
		default : ;break;
	}
}


void mostrar_caos(int caos_jugador,int caos_enemigo)//FUNCION QUE MUESTRA EN PANTALLA AL JUGADOR Y AL ENEMIGO EN BATALLA
{
	switch(caos_jugador)//MUESTRA JUGADOR VARIANDO SU TAMAÑO
	{
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
	
	
	
	switch(caos_enemigo)//MUESTRA AL ENEMIGO VARIANDO SU TAMAÑO
	{
		
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

void evolucion(int enemigo_conteo[20])//FUNCION ENCARGADA DE LA EVOLUCION DEL CAOTYK DEL JUGADOR
{
	int aux_evo = 0;//Variable que se usara como auxiliar del proceso de evolucion
	int i = 0;//contador
	aux_evo = enemigo_conteo[i];//Guarda el caotyk enemigo enfrentado en la ultima batalla realizada para luego comparar
	
	
	for(i=0;i<20;i++)
	{
		if(enemigo_conteo[i] < aux_evo)//Ciclo que busca cual a sido el enemigo que mas veces se a matado
		{
			aux_evo = enemigo_conteo[i];//se guarda el valor mayor obtenido
		}
	}
	
	//CADA EVOLUCION TIENE SU PROPIA CONDICION QUE SI SE LLEGA A CUMPLIR, EL VALOR DEL CAOTYK DEL JUGADOR CAMBIA, HACIENDO QUE AHORA SEA OTRO MOSNTRUO
	//evolucion de etapa bebe a entrenamiento
	if(victoria > 20 && aux_evo == 0 || victoria > 20 && aux_evo == 1)
	{
		caos_jugador = 1;	
	}else if(victoria > 20 && aux_evo == 2)
	{
		caos_jugador = 2;
	}
	
	//evolucion de etapa entrenamiento a adulto
	if(caos_jugador == 1 && victoria > 60 && aux_evo == 3)
	{
		caos_jugador = 3;
		
	}else if(caos_jugador == 1 && victoria > 60 && aux_evo == 4)
	{
		caos_jugador = 4;
		
	}else if(caos_jugador == 1 && victoria > 60 && aux_evo == 5)
	{
		caos_jugador = 5;
		
	}else if(caos_jugador == 2 && victoria > 60 && aux_evo == 6)
	{
		caos_jugador = 6;
		
	}else if(caos_jugador == 2 && victoria > 60 && aux_evo == 7)
	{
		caos_jugador = 7;
		
	}else if(caos_jugador == 2 && victoria > 60 && aux_evo == 8)
	{
		caos_jugador = 8;
	}
	
	//evolucion de tapa adulto a avanzado
	
	if(caos_jugador == 4 && victoria > 100 && aux_evo == 9)
	{
		caos_jugador = 9;
		
	}else if(caos_jugador == 5 && victoria > 100 && aux_evo == 10)
	{
		caos_jugador = 10;
		
	}else if(caos_jugador == 7 && victoria > 100 && aux_evo == 11)
	{
		caos_jugador = 11;
		
	}else if(caos_jugador == 8 && victoria > 100 && aux_evo == 12)
	{
		caos_jugador = 12;
	}
	
	//evolucion de etapa avanzado a mega
	
	if(caos_jugador == 9 && victoria > 150 && aux_evo == 13)
	{
		caos_jugador = 13;
		
	}else if(caos_jugador == 9 && victoria > 150 && aux_evo == 14)
	{
		caos_jugador = 14;
		
	}else if(caos_jugador == 9 && victoria > 150 && aux_evo == 15)
	{
		caos_jugador = 15;
		
	}else if(caos_jugador == 11 && victoria > 150 && aux_evo == 16)
	{
		caos_jugador = 16;
		
	}else if(caos_jugador == 11 && victoria > 150 && aux_evo == 17)
	{
		caos_jugador = 17;
		
	}else if(caos_jugador == 11 && victoria > 150 && aux_evo == 18)
	{
		caos_jugador = 18;
		
	}else if(caos_jugador == 12 && victoria > 150 && aux_evo == 19)
	{
		caos_jugador = 19;
	}
	
}//SE TERMINA LA FUNCION DE EVOLUCION

void registro()//SISTEMA DE ENCICLOPEDIA Y PUNTAJE PARA RANKING
{
	int registrado = 0; //Contador que se encarga de sumar +1 cada que se registra uno de los 20 caotyks que hay
	int i = 0;//contador
	int pos = 0;//posicion en la que te encuentres al leer la enciclopedia
	
	switch(caos_jugador)//ENCARGADO DE LLENAR LA ENCICLOPEDIA DEPENDIENDO DEL CAOTYK QUE TE TENGA Y QUE SE HAN TENIDO
	{
		case 0 : enciclopedia[0] = 1;break;
		case 1 : enciclopedia[1] = 1;break;
		case 2 : enciclopedia[2] = 1;break;
		case 3 : enciclopedia[3] = 1;break;
		case 4 : enciclopedia[4] = 1;break;
		case 5 : enciclopedia[5] = 1;break;
		case 6 : enciclopedia[6] = 1;break;
		case 7 : enciclopedia[7] = 1;break;
		case 8 : enciclopedia[8] = 1;break;
		case 9 : enciclopedia[9] = 1;break;
		case 10 : enciclopedia[10] = 1;break;
		case 11 : enciclopedia[11] = 1;break;
		case 12 : enciclopedia[12] = 1;break;
		case 13 : enciclopedia[13] = 1;break;
		case 14 : enciclopedia[14] = 1;break;
		case 15 : enciclopedia[15] = 1;break;
		case 16 : enciclopedia[16] = 1;break;
		case 17 : enciclopedia[17] = 1;break;
		case 18 : enciclopedia[18] = 1;break;
		case 19 : enciclopedia[19] = 1;break;
		default : ;break;
	}
	
	for(i=0;i<20;i++)//CICLO QUE VERIFICA SI ESTA REGISTRADO O NO EN LA ENCICLOPEDIA EL CAOTYK
	{	
		if(enciclopedia[i]==1)
		{
			registrado++;
		}
	}
	//VARIABLES LOCALES QUE FUNCIONAN COMO TIMER, COMO PAUSA ENTRE CADA CAMBIO DE IMAGEN PARA QUE NO SE CAMBIE A VELOCIDAD DE PROCESADOR
	int lapsoder = 0;
	int lapsoizq = 0;
	//===================
	
	while(!key[KEY_S])//ESTO SE REALIZA DENTRO DE LA ENCICLOPEDIA, YA QUE PARA SALIR SE NECESITA APRETAR LA TECLA S
	{
		puntaje = registrado *100 + (victoria * 100) - (derrota * 50);
		
		if(puntaje < 0)//Restriccion para que el puntaje no sea negativo, si llega a ser negativo se iguala a 0
		{
			puntaje = 0;
		}
		
		textprintf_ex(screen, font, 350,550, makecol(0, 0, 0),-1, "PUNTAJE : %d",puntaje); //Se imprime el puntaje actual en la enciclopedia
			
		if(pos == 0)//SE MANTIENE EN LA PRIMERA PAGINA DE LA ENCICLOPEDIA AL ENTRAR
		{
			destroy_bitmap(reg);//se libera bitmap
			reg = load_bitmap("media/dex/dex0.bmp",NULL);//se carga el bitmap de la enciclopedia correspondiente
			blit(reg,screen,0,0,0,0,800,600);//se imprime en pantalla
			textprintf_ex(screen, font, 350,550, makecol(0, 0, 0),-1, "PUNTAJE : %d",puntaje);//se vuelve a imprimir el puntaje para evitar fallos (sino parpadea)
		}			
			
		if(key[KEY_RIGHT])//SE AVANZA HACIA LA SIGUIENTE PAGINA DE LA ENCICLOPEDIA - A LA DERECHA
		{
			lapsoder++;//contador para disminuir velocidad de cambio
				
			if(lapsoder == 13)//llegado a el valor de 13 en el contador se pasa a la siguiente entrada de la enciclopedia
			{
				pos++;//contador para realizar el cambio de pagina en la enciclopedia
				lapsoder = 0;//se reinicia el contador
			}
			if(pos == 20)//restriccion para no pasarse de la cantidad maxima de entrada en la enciclopedia, en este caso son 20 asi que se deja en 19
			{
				pos = 19;
			}		
		}
		
		if(key[KEY_LEFT])//MISMA FUNCION QUE EL IF DE ARRIBA SOLO QUE ESTA VEZ HACIA LA IZQUIERDA
		{
			lapsoizq++;
				
			if(lapsoizq == 13)
			{
				pos--;
				lapsoizq = 0;
			}
			
			if(pos == -1)
			{
				pos = 0;
					
			}
		}//======================
		
		switch(pos)//CAMBIO A LA PAGINA CORRESPONDIENTE E IMPRESION SI SE TIENE REGISTRADA O NO LA PAGINA DE LA ENCICLOPEDIA
		{
			case 0: 
				destroy_bitmap(reg);
				reg = load_bitmap("media/dex/dex0.bmp",NULL);
				blit(reg,screen,0,0,0,0,800,600);	
			;break;
			
			case 1: 
				if(enciclopedia[1] == 1)
				{
					destroy_bitmap(reg);
					reg = load_bitmap("media/dex/dex1.bmp",NULL);
					blit(reg,screen,0,0,0,0,800,600);
				}else
				{
					destroy_bitmap(reg);
					reg = load_bitmap("media/dex/dexdesconocido.bmp",NULL);
					blit(reg,screen,0,0,0,0,800,600);
				}
			;break;
			
			case 2: 
				if(enciclopedia[2] == 1)
				{
					destroy_bitmap(reg);
					reg = load_bitmap("media/dex/dex2.bmp",NULL);
					blit(reg,screen,0,0,0,0,800,600);
				}else
				{
					destroy_bitmap(reg);
					reg = load_bitmap("media/dex/dexdesconocido.bmp",NULL);
					blit(reg,screen,0,0,0,0,800,600);
				}	
			;break;
		
			case 3: 
				if(enciclopedia[3] == 1)
				{
					destroy_bitmap(reg);
					reg = load_bitmap("media/dex/dex3.bmp",NULL);
					blit(reg,screen,0,0,0,0,800,600);
				}else
				{
					destroy_bitmap(reg);
					reg = load_bitmap("media/dex/dexdesconocido.bmp",NULL);
					blit(reg,screen,0,0,0,0,800,600);
				}
			;break;
			
			case 4: 
				if(enciclopedia[4] == 1)
				{
					destroy_bitmap(reg);
					reg = load_bitmap("media/dex/dex4.bmp",NULL);
					blit(reg,screen,0,0,0,0,800,600);
				}else
				{
					destroy_bitmap(reg);
					reg = load_bitmap("media/dex/dexdesconocido.bmp",NULL);
					blit(reg,screen,0,0,0,0,800,600);
				}
			;break;
			
			case 5: 
				if(enciclopedia[5] == 1)
				{
					destroy_bitmap(reg);
					reg = load_bitmap("media/dex/dex5.bmp",NULL);
					blit(reg,screen,0,0,0,0,800,600);	
				}else
				{
					destroy_bitmap(reg);
					reg = load_bitmap("media/dex/dexdesconocido.bmp",NULL);
					blit(reg,screen,0,0,0,0,800,600);
				}
			;break;
			
			case 6: 
				if(enciclopedia[6] == 1)
				{
					destroy_bitmap(reg);
					reg = load_bitmap("media/dex/dex6.bmp",NULL);
					blit(reg,screen,0,0,0,0,800,600);
						
				}else
				{
					destroy_bitmap(reg);
					reg = load_bitmap("media/dex/dexdesconocido.bmp",NULL);
					blit(reg,screen,0,0,0,0,800,600);
				}
			;break;
			
			case 7: 
				if(enciclopedia[7] == 1)
				{
					destroy_bitmap(reg);
					reg = load_bitmap("media/dex/dex7.bmp",NULL);
					blit(reg,screen,0,0,0,0,800,600);
						
				}else
				{
					destroy_bitmap(reg);
					reg = load_bitmap("media/dex/dexdesconocido.bmp",NULL);
					blit(reg,screen,0,0,0,0,800,600);
				}
			;break;
			
			case 8: 
				if(enciclopedia[8] == 1)
				{
					destroy_bitmap(reg);
					reg = load_bitmap("media/dex/dex8.bmp",NULL);
					blit(reg,screen,0,0,0,0,800,600);	
				}else
				{
					destroy_bitmap(reg);
					reg = load_bitmap("media/dex/dexdesconocido.bmp",NULL);
					blit(reg,screen,0,0,0,0,800,600);
				}
			;break;
				
			case 9: 
				if(enciclopedia[9] == 1)
				{
					destroy_bitmap(reg);
					reg = load_bitmap("media/dex/dex9.bmp",NULL);
					blit(reg,screen,0,0,0,0,800,600);		
				}else
				{
					destroy_bitmap(reg);
					reg = load_bitmap("media/dex/dexdesconocido.bmp",NULL);
					blit(reg,screen,0,0,0,0,800,600);
				}
			;break;
			
			case 10: 
				if(enciclopedia[10] == 1)
				{
					destroy_bitmap(reg);
					reg = load_bitmap("media/dex/dex10.bmp",NULL);
					blit(reg,screen,0,0,0,0,800,600);
				}else
				{
					destroy_bitmap(reg);
					reg = load_bitmap("media/dex/dexdesconocido.bmp",NULL);
					blit(reg,screen,0,0,0,0,800,600);
				}
			;break;
			
			case 11: 
				if(enciclopedia[11] == 1)
				{
					destroy_bitmap(reg);
					reg = load_bitmap("media/dex/dex11.bmp",NULL);
					blit(reg,screen,0,0,0,0,800,600);
				}else
				{
					destroy_bitmap(reg);
					reg = load_bitmap("media/dex/dexdesconocido.bmp",NULL);
					blit(reg,screen,0,0,0,0,800,600);
				}	
			;break;
		
			case 12: 
				if(enciclopedia[12] == 1)
				{
					destroy_bitmap(reg);
					reg = load_bitmap("media/dex/dex12.bmp",NULL);
					blit(reg,screen,0,0,0,0,800,600);
				}else
				{
					destroy_bitmap(reg);
					reg = load_bitmap("media/dex/dexdesconocido.bmp",NULL);
					blit(reg,screen,0,0,0,0,800,600);
				}
			;break;
			
			case 13: 
				if(enciclopedia[13] == 1)
				{
					destroy_bitmap(reg);
					reg = load_bitmap("media/dex/dex13.bmp",NULL);
					blit(reg,screen,0,0,0,0,800,600);
				}else
				{
					destroy_bitmap(reg);
					reg = load_bitmap("media/dex/dexdesconocido.bmp",NULL);
					blit(reg,screen,0,0,0,0,800,600);
				}
			;break;
			
			case 14: 
				if(enciclopedia[14] == 1)
				{
					destroy_bitmap(reg);
					reg = load_bitmap("media/dex/dex14.bmp",NULL);
					blit(reg,screen,0,0,0,0,800,600);	
				}else
				{
					destroy_bitmap(reg);
					reg = load_bitmap("media/dex/dexdesconocido.bmp",NULL);
					blit(reg,screen,0,0,0,0,800,600);
				}
			;break;
			
			case 15: 
				if(enciclopedia[15] == 1)
				{
					destroy_bitmap(reg);
					reg = load_bitmap("media/dex/dex15.bmp",NULL);
					blit(reg,screen,0,0,0,0,800,600);
						
				}else
				{
					destroy_bitmap(reg);
					reg = load_bitmap("media/dex/dexdesconocido.bmp",NULL);
					blit(reg,screen,0,0,0,0,800,600);
				}
			;break;
			
			case 16: 
				if(enciclopedia[16] == 1)
				{
					destroy_bitmap(reg);
					reg = load_bitmap("media/dex/dex16.bmp",NULL);
					blit(reg,screen,0,0,0,0,800,600);
						
				}else
				{
					destroy_bitmap(reg);
					reg = load_bitmap("media/dex/dexdesconocido.bmp",NULL);
					blit(reg,screen,0,0,0,0,800,600);
				}
			;break;
			
			case 17: 
				if(enciclopedia[17] == 1)
				{
					destroy_bitmap(reg);
					reg = load_bitmap("media/dex/dex17.bmp",NULL);
					blit(reg,screen,0,0,0,0,800,600);	
				}else
				{
					destroy_bitmap(reg);
					reg = load_bitmap("media/dex/dexdesconocido.bmp",NULL);
					blit(reg,screen,0,0,0,0,800,600);
				}
			;break;
				
			case 18: 
				if(enciclopedia[18] == 1)
				{
					destroy_bitmap(reg);
					reg = load_bitmap("media/dex/dex18.bmp",NULL);
					blit(reg,screen,0,0,0,0,800,600);		
				}else
				{
					destroy_bitmap(reg);
					reg = load_bitmap("media/dex/dexdesconocido.bmp",NULL);
					blit(reg,screen,0,0,0,0,800,600);
				}
			;break;
			
			case 19: 
				if(enciclopedia[19] == 1)
				{
					destroy_bitmap(reg);
					reg = load_bitmap("media/dex/dex19.bmp",NULL);
					blit(reg,screen,0,0,0,0,800,600);		
				}else
				{
					destroy_bitmap(reg);
					reg = load_bitmap("media/dex/dexdesconocidofinal.bmp",NULL);
					blit(reg,screen,0,0,0,0,800,600);
				}
			;break;
			
			default : ;break;	
		}	
	}
}//Finalizacion de la enciclopedia


void ranking()//FUNCION DE RANKING CON ENTRADA DE TEXTO .TXT GUARDADO EN UNA ESTRUCTURA GLOBAL
{
	int m = 0;//contador unico
	FILE *r_puntos;//Crear un archivo FILE llamado r_puntos
	r_puntos = fopen("rpunt.txt","rt");//cargar el .TXT en el archivo r_puntos

	for(m=0;m<4;m++)//ciclo que brina las variables a la estructura segun corresponda en el archivo TXT
	{
		fscanf(r_puntos,"%s ",puntitos[m].nombre);
		fscanf(r_puntos,"%d",puntitos[m].puntos);		
	}//fin del ciclo de rellenado de puntaje
	fclose(r_puntos);//cierre de archivo
	
}



